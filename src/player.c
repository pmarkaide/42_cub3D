/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:01:36 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/25 23:01:46 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	m->ray->floor = get_rgba(m->map->f[0], m->map->f[1], m->map->f[2], 255);
	m->ray->ceiling = get_rgba(m->map->c[0], m->map->c[1], m->map->c[2], 255);
	m->tex->no = mlx_load_png(m->map->no);
    m->tex->so = mlx_load_png(m->map->so);
    m->tex->we = mlx_load_png(m->map->we);
    m->tex->ea = mlx_load_png(m->map->ea);
	mirror_vert(m->tex->no);
	mirror_vert(m->tex->ea);
	player_in_map(m);
}
