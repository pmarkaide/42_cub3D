/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:46:43 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/27 14:20:11 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static void	load_image(t_macro *m)
{
	if (mlx_image_to_window(m->mlx_cub, m->scene_i, 0, 0) == -1)
	{
		write(2, "Error\nFailed to initialize window\n", 33);
		free_all(m);
	}
}

int	init_game(t_macro *m)
{
	if (check_pngs(m))
	{
		write(2, "Error\nFailed to load PNGs\n", 26);
		return (1);
	}
	m->width = 2880;
	m->height = 1620;
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

static int	check_argc(int argc)
{
	if (argc != 2)
	{
		write(2, "Error\nIncorrect number of arguments\n", 36);
		return (1);
	}
	return (0);
}

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
