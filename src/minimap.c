/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:20:28 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/05 16:58:00 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void render_minimap(t_macro *macro)
{
	size_t	x;
	size_t	y;

    if (!macro || !macro->map || !macro->map->map || !macro->m_mlx || !macro->m_mlx->img)
    {
        fprintf(stderr, "Invalid macro or map structure\n");
        return;
    }

	x = 0;
	while (x < (size_t)macro->map->w_map)
	{
		y = 0;
		while (y < (size_t)macro->map->h_map)
		{
			if (macro->map->map[x][y] == '1')
				mlx_put_pixel(macro->m_mlx->img, y * 5, x * 5, 0x00000000);
			else if (macro->map->map[x][y] == '0')
				mlx_put_pixel(macro->m_mlx->img, y * 5, x * 5, 0x00000000);
			y += 1;
		}
		x += 1;
	}

    // works
    // x = 0;
	// while (x < WIDTH)
	// {
	// 	y = 0;
	// 	while (y < HEIGHT)
	// 	{
	// 		if (y % 10 == 0)
	// 			mlx_put_pixel(macro->m_mlx->img, y , x , 0xFFFFFFFF);
	// 		else
	// 			mlx_put_pixel(macro->m_mlx->img, y , x , 0x00000000);
	// 		y += 1;
	// 	}
	// 	x += 1;
	// }
}
