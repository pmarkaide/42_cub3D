/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:20:28 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/17 13:26:22 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"


void draw_vision_cone(t_macro *macro)
{
    int x;
    int draw_x, draw_y;
    float ray_length;
    
    
    double camera_x;
    double ray_dir_x, ray_dir_y;
    int map_x, map_y;
    double side_dist_x, side_dist_y;
    double delta_dist_x, delta_dist_y;
    int step_x, step_y;
    int hit, side;
    
    
    float center_x = macro->pos_pl_x + BLOCK / 2;
    float center_y = macro->pos_pl_y + BLOCK / 2;
    
    x = 0;
    while (x < macro->width)
    {
        
        camera_x = 2 * x / (double)macro->width - 1;
        ray_dir_x = cos(macro->play_angle) + camera_x * cos(macro->play_angle + M_PI / 2);
        ray_dir_y = sin(macro->play_angle) + camera_x * sin(macro->play_angle + M_PI / 2);

        
        map_x = (int)(center_x / BLOCK);
        map_y = (int)(center_y / BLOCK);
        delta_dist_x = fabs(1 / ray_dir_x);
        delta_dist_y = fabs(1 / ray_dir_y);
        hit = 0;

        
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (center_x / BLOCK - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - center_x / BLOCK) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (center_y / BLOCK - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - center_y / BLOCK) * delta_dist_y;
        }

        
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (macro->map->map[map_y][map_x] == '1')
                hit = 1;
        }

        
        if (side == 0)
            ray_length = (map_x - center_x / BLOCK + 
                (1 - step_x) / 2) / ray_dir_x * BLOCK;
        else
            ray_length = (map_y - center_y / BLOCK + 
                (1 - step_y) / 2) / ray_dir_y * BLOCK;

        
        float dist = 0.0f;
        while (dist <= ray_length)
        {
            draw_x = center_x + (int)(ray_dir_x * dist);
            draw_y = center_y + (int)(ray_dir_y * dist);
            
            if (draw_x >= 0 && draw_x < (int)macro->map->w_map * 32 &&
                draw_y >= 0 && draw_y < (int)macro->map->h_map * 32)
            {
                int alpha = 255;
                int color = (255 << 24) | (255 << 16) | (255 << 8) | alpha;
                mlx_put_pixel(macro->mini_i, draw_x, draw_y, color);
            }
            dist += 0.5f;
        }
        x += 1;
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
