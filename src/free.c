/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:10:04 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/07 11:11:03 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_macro *macro)
{
	int	i;

	i = -1;
	if (macro->map)
	{
		if (macro->map->no)
			free(macro->map->no);
		if (macro->map->so)
			free(macro->map->so);
		if (macro->map->we)
			free(macro->map->we);
		if (macro->map->ea)
			free(macro->map->ea);
		if (macro->map->map)
		{
			while (++i < (int)macro->map->h_map)
				free(macro->map->map[i]);
			free(macro->map->map);
		}
		free(macro->map);
	}
}

void	free_macro(t_macro *macro)
{
	free_map(macro);
	/*if (macro->mlx_cub)
	{
		mlx_delete_image(macro->mlx_cub, macro->img);
		mlx_close_window(macro->mlx_cub);
		mlx_terminate(macro->mlx_cub);
	}*/
	free(macro);
}

void	free_and_exit(t_macro *macro)
{
	// write(2, "Error\n", 6);
	free_macro(macro);
	exit(1);
}
