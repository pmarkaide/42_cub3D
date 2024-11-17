/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:20:28 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/17 14:04:00 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"


void initialize_vision_ray(t_macro *macro, int x, double *ray_dir_x, double *ray_dir_y)
{
    double camera_x;
    float center_x;
    float center_y;
    
    center_x = macro->pos_pl_x + BLOCK / 2;
    center_y = macro->pos_pl_y + BLOCK / 2;
    camera_x = 2 * x / (double)macro->width - 1;
    *ray_dir_x = cos(macro->play_angle) + camera_x * cos(macro->play_angle + M_PI / 2);
    *ray_dir_y = sin(macro->play_angle) + camera_x * sin(macro->play_angle + M_PI / 2);
    macro->map_x = (int)(center_x / BLOCK);
    macro->map_y = (int)(center_y / BLOCK);
    macro->delta_dist_x = fabs(1 / *ray_dir_x);
    macro->delta_dist_y = fabs(1 / *ray_dir_y);
    macro->hit = 0;
}

void calculate_ray_steps(t_macro *macro, double ray_dir_x, double ray_dir_y)
{
    float center_x;
    float center_y;
    
    center_x = macro->pos_pl_x + BLOCK / 2;
    center_y = macro->pos_pl_y + BLOCK / 2;
    if (ray_dir_x < 0)
    {
        macro->step_x = -1;
        macro->side_dist_x = (center_x / BLOCK - macro->map_x) * macro->delta_dist_x;
    }
    else
    {
        macro->step_x = 1;
        macro->side_dist_x = (macro->map_x + 1.0 - center_x / BLOCK) * macro->delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        macro->step_y = -1;
        macro->side_dist_y = (center_y / BLOCK - macro->map_y) * macro->delta_dist_y;
    }
    else
    {
        macro->step_y = 1;
        macro->side_dist_y = (macro->map_y + 1.0 - center_y / BLOCK) * macro->delta_dist_y;
    }
}

void draw_ray(t_macro *macro, float ray_length, double ray_dir_x, double ray_dir_y)
{
    float dist;
    int draw_x;
    int draw_y;
    float center_x;
    float center_y;

    dist = 0.0f;
    center_x = macro->pos_pl_x + BLOCK / 2;
    center_y = macro->pos_pl_y + BLOCK / 2;
    while (dist <= ray_length)
    {
        draw_x = center_x + (int)(ray_dir_x * dist);
        draw_y = center_y + (int)(ray_dir_y * dist);
        if (draw_x >= 0 && draw_x < (int)macro->map->w_map * 32 &&
            draw_y >= 0 && draw_y < (int)macro->map->h_map * 32)
        {
            mlx_put_pixel(macro->mini_i, draw_x, draw_y, 
                get_rgba(255, 255, 255, 255));
        }
        dist += 0.5f;
    }
}

void draw_vision_cone(t_macro *macro)
{
    int x;
    float ray_length;
    double ray_dir_x;
    double ray_dir_y;
    float center_x;
    float center_y;
    
    x = 0;
    center_x = macro->pos_pl_x + BLOCK / 2;
    center_y = macro->pos_pl_y + BLOCK / 2;
    while (x < macro->width)
    {
        initialize_vision_ray(macro, x, &ray_dir_x, &ray_dir_y);
        calculate_ray_steps(macro, ray_dir_x, ray_dir_y);
        perform_dda(macro);
        
        if (macro->side == 0)
            ray_length = (macro->map_x - center_x / BLOCK + 
                (1 - macro->step_x) / 2) / ray_dir_x * BLOCK;
        else
            ray_length = (macro->map_y - center_y / BLOCK + 
                (1 - macro->step_y) / 2) / ray_dir_y * BLOCK;
        draw_ray(macro, ray_length, ray_dir_x, ray_dir_y);
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
