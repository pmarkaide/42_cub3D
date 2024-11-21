/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:46:43 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/21 13:02:28 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_game(t_macro *m)
{
	mlx_t	*first;

	first = mlx_init(800, 600, "Loading...", 0);
	mlx_get_monitor_size(0, &m->width, &m->height);
	mlx_terminate(first);
	m->width *= RATIO_SCREEN;
	m->height *= RATIO_SCREEN;
	m->mlx_cub = mlx_init(m->width, m->height, "cub3D", 0);
	m->images->scene_i = mlx_new_image(m->mlx_cub, m->width, m->height);
	m->images->mini_i = mlx_new_image(m->mlx_cub, m->map->w_map * BLOCK,
			m->map->h_map * BLOCK);
	if (!m->mlx_cub || !m->images->scene_i || !m->images->mini_i)
		return (write(2, "Error\nFailed to initialize game\n", 33), 1);
	load_images_into_struct(m);
	m->ray->pos_pl_x = m->map->start_x;
	m->ray->pos_pl_y = m->map->start_y;
	load_map(m);
	load_player(m);
	load_game(m);
	draw_minimap(m);
	mlx_image_to_window(m->mlx_cub, m->images->scene_i, 0, 0);
	mlx_image_to_window(m->mlx_cub, m->images->mini_i, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_macro	*m;

	m = NULL;
	if (argc != 2)
		return (write(2, "Error\nIncorrect number of arguments\n", 36), 1);
	m = init_macro(m);
	if (!m)
		return (write(2, "Error\nMalloc failed\n", 20), 1);
	read_input(argv[1], m);
	if (validate_map(m))
	{
		printf("Error\nInvalid map\n");
		free_macro(m);
		return (1);
	}
	if (init_game(m))
		return (1);
	mlx_loop_hook(m->mlx_cub, &load_game, m);
	mlx_key_hook(m->mlx_cub, &ft_hook, m);
	mlx_loop(m->mlx_cub);
	return (0);
}
