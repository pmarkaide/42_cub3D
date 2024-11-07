/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:20:28 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/07 11:36:56 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static void	render_block(t_macro *macro, mlx_image_t *img, size_t y, size_t x)
{
	int	exit_code;

	exit_code = mlx_image_to_window(macro->mlx_cub, img, y * 32, x * 32);
	if (exit_code == -1)
		free_and_exit(macro);
}

void	render_minimap(t_macro *macro)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < macro->map->h_map)
	{
		y = 0;
		while (y < macro->map->w_map)
		{
			render_block(macro, macro->minimap->background, y, x);
			if (macro->map->map[x][y] == '1')
				render_block(macro, macro->minimap->wall, y, x);
			y += 1;
		}
		x += 1;
	}
	//render_block(macro, macro->player, macro->map->start_y, macro->map->start_x);
}
