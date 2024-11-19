/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:46:15 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 10:48:28 by pmarkaid         ###   ########.fr       */
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

void	correct_player_pos_in_edge(t_macro *macro)
{
	if (macro->pos_pl_x < 32)
		macro->pos_pl_x = 32;
	else if (macro->pos_pl_x >= (int)macro->map->w_map * 32 - 64)
		macro->pos_pl_x = macro->map->w_map * 32 - 64;
	if (macro->pos_pl_y < 32)
		macro->pos_pl_y = 32;
	else if (macro->pos_pl_y >= (int)macro->map->h_map * 32 - 64)
		macro->pos_pl_y = macro->map->h_map * 32 - 64;
}


