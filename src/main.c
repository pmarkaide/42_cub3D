/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:46:43 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/15 16:03:08 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int init_game(t_macro *macro)
{
	mlx_t *first = mlx_init(800, 600, "Loading...", 0);
	mlx_get_monitor_size(0, &macro->width, &macro->height);
	mlx_terminate(first);
	macro->width *= RATIO_SCREEN;
	macro->height *= RATIO_SCREEN;
	macro->mlx_cub = mlx_init(macro->width, macro->height, "cub3D", 0);
	macro->scene_i = mlx_new_image(macro->mlx_cub, macro->width, macro->height);
	macro->mini_i = mlx_new_image(macro->mlx_cub, macro->map->w_map * 32, macro->map->h_map * 32);
	if (!macro->mlx_cub || !macro->scene_i || !macro->mini_i)
		return (write(2, "Error\nFailed to initialize mlx or create images\n", 48), 1);
	load_images_into_struct(macro);
	load_map(macro);
	load_player(macro);
	load_game(macro);
	return (0);
}

int	main(int argc, char **argv)
{
	t_macro	*macro;

	macro = NULL;
	if (argc != 2)
		return (write(2, "Error\nIncorrect number of arguments\n", 36), 1);
	macro = init_macro(macro);
	if (!macro)
		return (write(2, "Error\nMalloc failed\n", 20), 1);
	read_input(argv[1], macro);
	if (validate_map(macro))
	{
		printf("Error\nInvalid map\n");
		free_and_exit(macro);
		return (1);
	}
	if (init_game(macro))
		return (1);
	mlx_loop_hook(macro->mlx_cub, &load_game, macro);
	mlx_key_hook(macro->mlx_cub, &ft_hook, macro);
	mlx_loop(macro->mlx_cub);
	mlx_terminate(macro->mlx_cub);
	return (0);
}
