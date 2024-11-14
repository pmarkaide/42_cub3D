/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:46:43 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/12 20:46:52 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_macro	*macro;
	mlx_t	*first;

	macro = NULL;
	if (argc != 2)
		return (write(2, "Error\nIncorrect number of arguments\n", 36), 1);
	macro = init_macro(macro);
	if (!macro)
		return (write(2, "Error\nMalloc failed\n", 20), 1);
	read_input(argv[1], macro);
	if (validate_map(macro))
	{
		ft_printf(2, "Map validation failed\n");
		return (1);
	}
	
	/************* NUEVO CODIGO */
	load_map(macro);
	first = mlx_init(800, 600, "Loading...", 0);
    mlx_get_monitor_size(0, &macro->width, &macro->height);
    printf("width %d height %d \n", macro->width, macro->height);
    mlx_terminate(first);
    macro->width *= RATIO_SCREEN;
    macro->height *= RATIO_SCREEN;
    macro->mlx_cub = mlx_init(macro->width, macro->height, "cub3D", 0);
    load_player(macro);
	
	load_images_into_struct(macro);
	macro->img = mlx_new_image(macro->mlx_cub, macro->width, macro->height);
	mlx_image_to_window(macro->mlx_cub, macro->img, 0, 0);
	//load_game(macro);
	render_minimap(macro);
	mlx_loop_hook(macro->mlx_cub, &load_game, macro);

    mlx_key_hook(macro->mlx_cub, &ft_hook, macro);
    mlx_loop(macro->mlx_cub);
    mlx_terminate(macro->mlx_cub);
    return (0);

	

	// eval_file(argv[1]);
	// map = read_file(argv[1]);
	// eval_elements(map);
}
