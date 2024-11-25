/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:46:43 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/25 14:36:59 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_pngs(t_macro *m)
{
	mlx_texture_t	*tmp;
	
	printf("LLEGUE\n");
	tmp = mlx_load_png(m->map->no);
	if (!tmp)
		return (1);
    mlx_delete_texture(tmp);
	tmp = mlx_load_png(m->map->so);
	if (!tmp)
		return (1);
	mlx_delete_texture(tmp);
	tmp = mlx_load_png(m->map->we);
	if (!tmp)
		return (1);
	mlx_delete_texture(tmp);
	tmp = mlx_load_png(m->map->ea);
	if (!tmp)
		return (1);
	mlx_delete_texture(tmp);
	return (0);
}

int	init_game(t_macro *m)
{
	mlx_t	*first;

	first = mlx_init(800, 600, "Loading...", 0);
	if (!first)
		return (write(2, "Error\nFailed to initialize gam1\n", 33), 1); //hacer free
	mlx_get_monitor_size(0, &m->width, &m->height);
	mlx_terminate(first);
	printf("CONTROL1\n");
	m->width *= RATIO_SCREEN;
	m->height *= RATIO_SCREEN;
	m->mlx_cub = mlx_init(m->width, m->height, "cub3D", 0);
	printf("CONTROL2\n");
	if (!m->mlx_cub)
		return (write(2, "Error\nFailed to initialize gam2\n", 33), 1); // hacer free
	m->images->scene_i = mlx_new_image(m->mlx_cub, m->width, m->height);
	// m->images->mini_i = mlx_new_image(m->mlx_cub, m->map->w_map * BLOCK,
	// 		m->map->h_map * BLOCK);
	if (!m->mlx_cub || !m->images->scene_i)// || !m->images->mini_i)
		return (write(2, "Error\nFailed to initialize gam3\n", 33), 1);
	
	//load_images_into_struct(m);
	m->ray->pos_pl_x = m->map->start_x;
	m->ray->pos_pl_y = m->map->start_y;
	if (check_pngs(m))
		return (1); // hacer free y salir; igual hay que meter función de exit
	printf("CONTROL3\n");
	load_map(m);
	printf("CONTROL4\n");
	load_player(m);
	//load_game(m);
	//draw_minimap(m);
	mlx_image_to_window(m->mlx_cub, m->images->scene_i, 0, 0);
	//mlx_image_to_window(m->mlx_cub, m->images->mini_i, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_macro	*m;

	m = NULL;
	if (argc != 2)
		return (write(2, "Error\nIncorrect number of arguments\n", 36), 1);
	m = init_macro(m);
	printf("INIT MACRO\n");
	if (!m)
		return (write(2, "Error\nMalloc failed\n", 20), 1);
	read_input(argv[1], m);
	printf("READ INPUT\n");
	if (init_game(m))
		return (1);
	printf("INIT GAME\n");
	mlx_key_hook(m->mlx_cub, &ft_hook, m);
	mlx_loop_hook(m->mlx_cub, &load_game, m);
	mlx_loop(m->mlx_cub);
	return (0);
}
