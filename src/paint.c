/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:26:44 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/25 23:15:39 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart;

	if (x > image->width || y > image->height)
		return (0xFF000000);
	pixelstart = image->pixels + (y * image->width + x) * sizeof(uint32_t);
	return (get_rgba(*(pixelstart), *(pixelstart + 1), *(pixelstart + 2),
			*(pixelstart + 3)));
}

void	paint_background(t_macro *m)
{
	int	y;
	int	x;

	y = 0;
	while (y < (m->height) / 2)
	{
		x = 0;
		while (x < m->width)
			mlx_put_pixel(m->images->scene_i, x++, y, m->ray->ceiling);
		y++;
	}
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
			mlx_put_pixel(m->images->scene_i, x++, y, m->ray->floor);
		y++;
	}
}
