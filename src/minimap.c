/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:20:28 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/17 12:55:37 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"


void draw_vision_cone(t_macro *macro)
{
    int x;
    int draw_x, draw_y;
    float ray_length;
    int max_distance = 64;

    x = 0;
    while (x < macro->width)
    {
        macro->camera_x = 2 * x / (double)macro->width - 1;
        macro->ray_dir_x = cos(macro->play_angle) + macro->camera_x * cos(macro->play_angle + M_PI / 2);
        macro->ray_dir_y = sin(macro->play_angle) + macro->camera_x * sin(macro->play_angle + M_PI / 2);
        
        ray_length = macro->perp_wall_dist * BLOCK;
        ray_length = fmin(ray_length, max_distance);

        float dist = 0.0f;
        while (dist <= ray_length)
        {
            draw_x = macro->pos_pl_x + (BLOCK / 2) + (int)(macro->ray_dir_x * dist);
            draw_y = macro->pos_pl_y + (BLOCK / 2) + (int)(macro->ray_dir_y * dist);
            
            if (draw_x >= 0 && draw_x < (int)macro->map->w_map * BLOCK &&
                draw_y >= 0 && draw_y < (int)macro->map->h_map * BLOCK)
            {
                int alpha = 255 - (int)((dist / ray_length) * 200);
                int color = (255 << 24) | (255 << 16) | (255 << 8) | alpha; // Yellow with fade
                mlx_put_pixel(macro->mini_i, draw_x, draw_y, color);
            }
            dist += 0.5f;
        }
        x += 4;
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

void correct_player_pos_in_edge(t_macro *macro, int *adj_x, int *adj_y) {
    *adj_x = macro->pos_pl_x;
    *adj_y = macro->pos_pl_y;

    if (*adj_x < 32)
        *adj_x = 32;
    else if (*adj_x >= (int)macro->map->w_map * 32 - 64)
        *adj_x = macro->map->w_map * 32 - 64;

    if (*adj_y < 32)
        *adj_y = 32;
    else if (*adj_y >= (int)macro->map->h_map * 32 - 64)
        *adj_y = macro->map->h_map * 32 - 64;
}

void draw_minimap(t_macro *macro)
{
	size_t	x;
	size_t	y;
    int     adj_x;
    int     adj_y;

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
    correct_player_pos_in_edge(macro, &adj_x, &adj_y);
    printf("player position: %d, %d\n", adj_x, adj_y);
	put_img_to_img(macro->mini_i, macro->minimap->player, adj_x, adj_y);
  draw_vision_cone(macro);
}
