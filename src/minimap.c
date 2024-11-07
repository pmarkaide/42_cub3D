/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:20:28 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/07 11:11:03 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

// void render_minimap(t_macro *macro)
// {
// 	size_t	x;
// 	size_t	y;

//     if (!macro || !macro->map || !macro->map->map || !macro->mlx_cub || !macro->img)
//     {
//         fprintf(stderr, "Invalid macro or map structure\n");
//         return;
//     }

// 	x = 0;
// 	while (x < (size_t)macro->map->w_map)
// 	{
// 		y = 0;
// 		while (y < (size_t)macro->map->h_map)
// 		{
// 			if (macro->map->map[x][y] == '1')
// 				mlx_put_pixel(macro->img, y * 5, x * 5, 0x00000000);
// 			else if (macro->map->map[x][y] == '0')
// 				mlx_put_pixel(macro->img, y * 5, x * 5, 0x00000000);
// 			y += 1;
// 		}
// 		x += 1;
// 	}

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
	while (x < macro->map->w_map)
	{
		y = 0;
		while (y < macro->map->h_map)
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
