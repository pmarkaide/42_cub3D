/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:46:43 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/12/30 20:19:09 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// #define RATIO_SCREEN 0.75 // Removed this line

/**
 * Checks if the PNG files are actual PNG files and can be loaded
 * 
 * @param m Pointer to the macro structure containing png path.
 * @return 1 if any PNG file fails to load, otherwise 0.
 */
static int	check_pngs(t_macro *m)
{
	mlx_texture_t	*tmp;

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

/**
 * Adjusts the screen size to be 75% of the monitor size.
 * 
 * @param m Pointer to the macro structure containing screen dimensions.
 */
static void	adjust_screen_size(t_macro *m)
{
	mlx_t	*first;

	first = mlx_init(800, 600, "Loading...", 0);
	mlx_get_monitor_size(0, &m->width, &m->height);
	ft_printf(1, "width %d height %d \n", m->width, m->height);
	mlx_terminate(first);
	m->width *= RATIO_SCREEN;
	m->height *= RATIO_SCREEN;
}

/**
 * Loads the main game image into the window.
 * 
 * @param m Pointer to the macro structure containing mlx and image information.
 */
static void	load_image(t_macro *m)
{
	if (mlx_image_to_window(m->mlx_cub, m->scene_i, 0, 0) == -1)
	{
		write(2, "Error\nFailed to initialize window\n", 33);
		free_all(m);
	}
}

/**
 * Initializes the game by setting up the window, loading textures, and initializing player position.
 * 
 * @param m Pointer to the macro structure containing game information.
 * @return 1 if initialization fails, otherwise 0.
 */
int	init_game(t_macro *m)
{
	if (check_pngs(m))
	{
		write(2, "Error\nFailed to load PNGs\n", 26);
		return (1);
	}
	adjust_screen_size(m);
	m->mlx_cub = mlx_init(m->width, m->height, "cub3D", 0);
	if (!m->mlx_cub)
	{
		write(2, "Error\nFailed to initialize game\n", 33);
		return (1);
	}
	m->scene_i = mlx_new_image(m->mlx_cub, m->width, m->height);
	if (!m->mlx_cub || !m->scene_i)
	{
		write(2, "Error\nFailed to initialize game\n", 33);
		return (1);
	}
	m->ray->pos_pl_x = m->map->start_x;
	m->ray->pos_pl_y = m->map->start_y;
	load_map(m);
	load_player(m);
	load_image(m);
	return (0);
}

/**
 * Checks if the correct number of arguments is provided.
 * 
 * @param argc Argument count.
 * @return 1 if the number of arguments is incorrect, otherwise 0.
 */
static int	check_argc(int argc)
{
	if (argc != 2)
	{
		write(2, "Error\nIncorrect number of arguments\n", 36);
		return (1);
	}
	return (0);
}

/**
 * Main function caller.
 * 
 * Checks for correct arguments and input file.
 * Initializes mlx library and keeps running until user exits.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 1 if initialization fails, otherwise 0.
 */
int	main(int argc, char **argv)
{
	t_macro	*m;

	m = NULL;
	if (check_argc(argc))
		return (1);
	m = init_macro(m);
	if (!m)
		return (1);
	if (read_input(argv[1], m))
		free_all(m);
	if (init_game(m))
		free_all(m);
	mlx_key_hook(m->mlx_cub, &ft_hook, m);
	mlx_loop_hook(m->mlx_cub, &load_game, m);
	mlx_loop(m->mlx_cub);
	free_all(m);
	return (0);
}
