/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:01:36 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/25 16:36:23 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

int	radian_side(double angle, int side)
{
	if (side)
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (!side)
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	cross_lines(double angle, float *crossed, float *step, int x_dda)
{
	if (x_dda)
	{
		if (angle > 0 && angle < M_PI)
		{
			*crossed += BLOCK;
			return (-1);
		}
		*step *= -1;
		return (1);
	}
	if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
	{
		*crossed += BLOCK;
		return (-1);
	}
	*step *= -1;
	return (1);
}

int	wall_hit(float x, float y, t_macro *m)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / BLOCK);
	y_m = floor (y / BLOCK);
	if ((y_m >= m->map->h_map || x_m >= m->map->w_map))
		return (0);
	if (m->map->grid[y_m] && x_m <= (int)ft_strlen(m->map->grid[y_m]))
		if (m->map->grid[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	x_dda(t_macro *m, double angle)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = BLOCK;
	x_step = BLOCK / (sin(angle) / cos(angle));
	h_y = floor(m->ray->pos_pl_y / BLOCK) * BLOCK;
	pixel = cross_lines(angle, &h_y, &y_step, 1);
	h_x = m->ray->pos_pl_x + (h_y - m->ray->pos_pl_y) / (sin(angle) / cos(angle));
	if ((radian_side(angle, 0) && x_step > 0) || (!radian_side(angle, 0) && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, m))
	{
		h_x += x_step;
		h_y += y_step;
	}
	m->ray->ray_dir_hx = h_x;
	m->ray->ray_dir_hy = h_y;
	return (sqrt(pow(h_x - m->ray->pos_pl_x, 2) + pow(h_y - m->ray->pos_pl_y, 2)));
}

float	y_dda(t_macro *m, double angle)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = BLOCK;
	y_step = BLOCK * (sin(angle) / cos(angle));
	v_x = floor(m->ray->pos_pl_x / BLOCK) * BLOCK;
	pixel = cross_lines(angle, &v_x, &x_step, 0);
	v_y = m->ray->pos_pl_y + (v_x - m->ray->pos_pl_x) * (sin(angle) / cos(angle));
	if ((radian_side(angle, 1) && y_step < 0) || (!radian_side(angle, 1) && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, m))
	{
		v_x += x_step;
		v_y += y_step;
	}
	m->ray->ray_dir_vx = v_x;
	m->ray->ray_dir_vy = v_y;
	return (sqrt(pow(v_x - m->ray->pos_pl_x, 2) + pow(v_y - m->ray->pos_pl_y, 2)));
}


float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

mlx_texture_t	*get_texture(t_macro *m, int flag)
{
	m->ray->ray_angle = nor_angle(m->ray->ray_angle);
	if (flag == 0)
	{
		if (m->ray->ray_angle > M_PI / 2 && m->ray->ray_angle < 3 * (M_PI / 2))
			return (m->tex->ea);
		else
			return (m->tex->we);
	}
	else
	{
		if (m->ray->ray_angle> 0 && m->ray->ray_angle < M_PI)
			return (m->tex->no);
		else
			return (m->tex->so);
	}
}

double	get_x_o(mlx_texture_t	*texture, t_macro *m)
{
	double	x_o;

	if (m->ray->hit == 1)
		x_o = (int)fmodf((m->ray->ray_dir_hx * (texture->width / BLOCK)), texture->width);
	else
		x_o = (int)fmodf((m->ray->ray_dir_vy * (texture->width / BLOCK)), texture->width);
	return (x_o);
}

void	my_mlx_pixel_put(t_macro *m, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= m->width)
		return ;
	if (y < 0)
		return ;
	else if (y >= m->height)
		return ;
	mlx_put_pixel(m->images->scene_i, x, y, color);
}

void	draw_wall(t_macro *m, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(m, m->ray->hit);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, m);
	y_o = (t_pix - (m->height / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(m, m->ray->index, t_pix, reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}
void	draw_floor_ceiling(t_macro *m, int ray, int t_pix, int b_pix)
{
	int		i;
	int		c;

	i = b_pix;
	c = m->ray->floor;
	while (i < m->height)
		my_mlx_pixel_put(m, ray, i++, c);
	c = m->ray->ceiling;
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(m, ray, i++, c);
}

void	do_wall(t_macro *m, int vertical)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	m->ray->distance *= cos(nor_angle(m->ray->ray_angle - m->ray->play_angle));
	wall_h = (BLOCK / m->ray->distance) * ((m->width / 2) / \
	tan(m->ray->play_view / 2));
	b_pix = (m->height / 2) + (wall_h / 2);
	t_pix = (m->height / 2) - (wall_h / 2);
	if (b_pix > m->height)
		b_pix = m->height;
	if (t_pix < 0)
		t_pix = 0;
	m->ray->index = vertical;
	
	//paint_background(m);
	
	draw_floor_ceiling(m, vertical, b_pix, t_pix);
	draw_wall(m, t_pix, b_pix, wall_h);
}

void	raycast(t_macro *m)
{
	double x_cross;
	double y_cross;
	int	vertical;

	vertical = 0;
	m->ray->ray_angle = m->ray->play_angle - (m->ray->play_view / 2);
	while (vertical < m->width)
	{
		m->ray->hit = 0;
		x_cross = x_dda(m, fmod(m->ray->ray_angle, 2 * M_PI));
		y_cross = y_dda(m, fmod(m->ray->ray_angle, 2 * M_PI));
		if (x_cross < y_cross)
		{
			m->ray->distance = x_cross;
			m->ray->hit = 1;
		}
		else
			m->ray->distance = y_cross;
		do_wall(m, vertical);
		vertical++;
		m->ray->ray_angle += m->ray->play_view / m->width;
	}
}


void	move(t_macro *m)
{
	get_wsda(m, 0, 0);
	move_rotate(m);
}

void	load_game(void *param)
{
	t_macro	*m;

	m = (t_macro *)param;
	mlx_delete_image(m->mlx_cub, m->images->scene_i);
	m->images->scene_i = mlx_new_image(m->mlx_cub, m->width, m->height);
	move(m);
	raycast(m);
	mlx_image_to_window(m->mlx_cub, m->images->scene_i, 0, 0);
}

void	load_player(t_macro *m)
{
	m->ray->pos_pl_x = (m->map->start_x * BLOCK) + (BLOCK / 2);
	m->ray->pos_pl_y = (m->map->start_y * BLOCK) + (BLOCK / 2);
	m->ray->play_view = M_PI * ANGLE_VIEW / 180;
	if (m->map->orientation == 'N')
		m->ray->play_angle = 3 * M_PI / 2;
	else if (m->map->orientation == 'E')
		m->ray->play_angle = 0;
	else if (m->map->orientation == 'S')
		m->ray->play_angle = M_PI / 2;
	else if (m->map->orientation == 'W')
		m->ray->play_angle = M_PI;
}

void	player_in_map(t_macro *m)
{
	int	y;
	int	x;

	y = 0;
	while (m->map->grid[y] != NULL)
	{
		x = 0;
		while (m->map->grid[y][x])
		{
			if (m->map->grid[y][x] == 'N' || m->map->grid[y][x] == 'S'
				|| m->map->grid[y][x] == 'E' || m->map->grid[y][x] == 'W')
			{
				m->map->start_x = x;
				m->map->start_y = y;
				m->map->orientation = m->map->grid[y][x];
				m->map->grid[y][x] = '0';
				break ;
			}
			x++;
		}
		y++;
	}
}

void mirror_vert(mlx_texture_t *texture)
{
    int width = texture->width;
    int height = texture->height;
    uint32_t *pixels = (uint32_t *)texture->pixels;
    uint32_t temp;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            int left_index = y * width + x;
            int right_index = y * width + (width - 1 - x);

            // Swap the pixels
            temp = pixels[left_index];
            pixels[left_index] = pixels[right_index];
            pixels[right_index] = temp;
        }
    }

}

void	load_map(t_macro *m)
{
	printf("CONTROL44\n");
	m->ray->floor = get_rgba(m->map->f[0], m->map->f[1], m->map->f[2], 255);
	m->ray->ceiling = get_rgba(m->map->c[0], m->map->c[1], m->map->c[2], 255);
	printf("CONTROL45\n");
	m->tex->no = mlx_load_png(m->map->no);
    m->tex->so = mlx_load_png(m->map->so);
    m->tex->we = mlx_load_png(m->map->we);
    m->tex->ea = mlx_load_png(m->map->ea);
	mirror_vert(m->tex->no);
	mirror_vert(m->tex->ea);
	// mirror_vert(m->tex->we);
	printf("CONTROL5\n");
	player_in_map(m);
}
