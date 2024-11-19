/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:22:37 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 13:00:37 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart;

	if (x > image->width || y > image->height)
		return (0xFF000000);
	pixelstart = image->pixels + (y * image->width + x) * sizeof(uint32_t);
	return (get_rgba(*(pixelstart), *(pixelstart + 1), *(pixelstart + 2),
			*(pixelstart + 3)));
}

static int	put_pixel_valid(mlx_image_t *img, uint32_t x, uint32_t y)
{
	return (x < img->width && y < img->height && mlx_get_pixel(img, x, y) != 0);
}

void	put_img2img(mlx_image_t *dst, mlx_image_t *src, int x, int y)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			if (put_pixel_valid(src, i, j))
				mlx_put_pixel(dst, x + i, y + j, mlx_get_pixel(src, i, j));
			j++;
		}
		i++;
	}
}
