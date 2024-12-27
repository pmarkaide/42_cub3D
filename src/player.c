/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:01:36 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/12/27 21:07:56 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Main game loop. At each keystroke, deletes the old image,
 * calculates the new position of the player and do the raycasting.
 * Then the image is rendered into the window.
 * 
 * @param param Pointer to the macro structure containing game information.
 */
void	load_game(void *param)
{
	t_macro	*m;

	m = (t_macro *)param;
	mlx_delete_image(m->mlx_cub, m->scene_i);
	m->scene_i = mlx_new_image(m->mlx_cub, m->width, m->height);
	move(m);
	raycast(m);
	mlx_image_to_window(m->mlx_cub, m->scene_i, 0, 0);
}

/**
 * Initializes the player's position and view angle at spawn point.
 * 
 * @param m Pointer to the macro structure containing player and map information.
 */
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

/**
 * Finds the player's initial position and orientation in the map.
 * 
 * @param m Pointer to the macro structure containing map information.
 */
void	player_in_map(t_macro *m)
{
	int	y;
	int	x;

	y = 0;
	while (m->map->buff[y] != NULL)
	{
		x = 0;
		while (m->map->buff[y][x])
		{
			if (m->map->buff[y][x] == 'N' || m->map->buff[y][x] == 'S'
				|| m->map->buff[y][x] == 'E' || m->map->buff[y][x] == 'W')
			{
				m->map->start_x = x;
				m->map->start_y = y;
				m->map->orientation = m->map->buff[y][x];
				m->map->buff[y][x] = '0';
				break ;
			}
			x++;
		}
		y++;
	}
}

/**
 * Mirrors the texture vertically.
 * 
 * @param texture Pointer to the texture to be mirrored.
 * @param left Index of the left pixel.
 * @param right Index of the right pixel.
 */
void	mirror_vert(mlx_texture_t *texture, int left, int right)
{
	uint32_t	*pixels;
	uint32_t	temp;
	uint32_t	y;
	uint32_t	x;

	pixels = (uint32_t *)texture->pixels;
	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width / 2)
		{
			left = y * texture->width + x;
			right = y * texture->width + (texture->width - 1 - x);
			temp = pixels[left];
			pixels[left] = pixels[right];
			pixels[right] = temp;
			x++;
		}
		y++;
	}
}

/**
 * Loads the map textures and initializes the player's position.
 * 
 * @param m Pointer to the macro structure containing map and texture information.
 */
void	load_map(t_macro *m)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	m->ray->floor = get_rgba(m->map->f[0], m->map->f[1], m->map->f[2], 255);
	m->ray->ceiling = get_rgba(m->map->c[0], m->map->c[1], m->map->c[2], 255);
	m->tex->no = mlx_load_png(m->map->no);
	m->tex->so = mlx_load_png(m->map->so);
	m->tex->we = mlx_load_png(m->map->we);
	m->tex->ea = mlx_load_png(m->map->ea);
	mirror_vert(m->tex->no, left, right);
	mirror_vert(m->tex->ea, left, right);
	player_in_map(m);
}
