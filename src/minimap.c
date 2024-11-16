/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:20:28 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/16 12:35:39 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"


void draw_cone(t_macro *macro) {

	// int i = 0;
	// while(i < 50)
	// {
	// 	mlx_put_pixel(macro->scene_i, macro->start_x * 32 + 15 + i, macro->start_y * 32 + 15 + i, 0xffff00);
	// 	mlx_put_pixel(macro->scene_i, macro->start_x * 32 + 15 + i, macro->start_y * 32 + 15 - i, 0xffff00);
	// 	i++;
	// }
    float angle_step = 0.001f;  // Adjust this for smoothness of the filled cone
    float max_distance = 70;   // Maximum distance of the cone's vision
    float vision_angle = M_PI / 4;  // Define the cone's angle (e.g., 45 degrees)

    // Loop over angles from the left edge to the right edge of the cone
    for (float angle = -vision_angle / 2; angle <= vision_angle / 2; angle += angle_step) {
        // Draw a line from the center to the maximum distance at this angle
        for (float dist = 0; dist <= max_distance; dist++) {
            int x = macro->start_x * 32 + 15 + (int)(cos(angle) * dist);
            int y = macro->start_y * 32 + 15 + (int)(sin(angle) * dist);
            mlx_put_pixel(macro->scene_i, x, y, 0xFFFF00);  // Draw pixel in the cone
        }
    }
}

int get_rgba(int r, int g, int b, int a) {
  return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * In MLX42 Colors are as follows:
 * 0000 0000 A (1st byte) -> uint8_t because it's 8 bits
 * 0000 0000 R (2nd byte)
 * 0000 0000 G (3rd byte)
 * 0000 0000 B (4th byte)
 **/
int32_t mlx_get_pixel(mlx_image_t* image, uint32_t x, uint32_t y) {
  if (x > image->width || y > image->height)
    return 0xFF000000;
  uint8_t* pixelstart = image->pixels + (y * image->width + x) * sizeof(uint32_t);
  return get_rgba(*(pixelstart), *(pixelstart + 1), * (pixelstart + 2), *(pixelstart + 3));
}

static int put_pixel_valid(mlx_image_t* img, uint32_t x, uint32_t y) {
    return (x < img->width && y < img->height && mlx_get_pixel(img, x, y) != 0);
}

void  put_img_to_img(mlx_image_t* dst, mlx_image_t* src, int x, int y) {
  size_t i;
  size_t j;

  i = 0;
  while(i < src->width) {
    j = 0;
    while (j < src->height) {
      if (put_pixel_valid(src, i, j))
        mlx_put_pixel(dst, x + i, y + j, mlx_get_pixel(src, i, j));
      j++;
    }
    i++;
  }
}


void draw_minimap(t_macro *macro)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < macro->map->h_map)
	{
		y = 0;
		while (y < macro->map->w_map)
		{
			put_img_to_img(macro->mini_i, macro->minimap->background, y*32, x*32);
			if (macro->map->map[x][y] == '1')
				put_img_to_img(macro->mini_i, macro->minimap->wall, y*32, x*32);
			y += 1;
		}
		x += 1;
	}
	put_img_to_img(macro->mini_i, macro->minimap->player, macro->pos_pl_x, macro->pos_pl_y);
}
