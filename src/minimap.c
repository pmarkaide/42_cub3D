/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:20:28 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/14 12:19:36 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"


void draw_cone(t_macro *macro) {

	// int i = 0;
	// while(i < 50)
	// {
	// 	mlx_put_pixel(macro->img, macro->start_x * 32 + 15 + i, macro->start_y * 32 + 15 + i, 0xffff00);
	// 	mlx_put_pixel(macro->img, macro->start_x * 32 + 15 + i, macro->start_y * 32 + 15 - i, 0xffff00);
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
            mlx_put_pixel(macro->img, x, y, 0xFFFF00);  // Draw pixel in the cone
        }
    }
}
	


static void	render_block(t_macro *macro, mlx_image_t *img, size_t y, size_t x)
{
	int32_t	exit_code;

	exit_code = mlx_image_to_window(macro->mlx_cub, img, y * 32, x * 32);
	if (exit_code == -1)
		free_and_exit(macro);
	printf("exit:_code: %d, img: %d\n", exit_code, img->instances->z);
	mlx_set_instance_depth(&img->instances[exit_code], 2);
}

void remove_minimap(t_macro *macro) {
    mlx_delete_image(macro->mlx_cub, macro->minimap->background);
    mlx_delete_image(macro->mlx_cub, macro->minimap->wall);
    mlx_delete_image(macro->mlx_cub, macro->minimap->player);
}

void	render_minimap(t_macro *macro)
{
	size_t	x;
	size_t	y;
	

	x = 0;
    remove_minimap(macro);
    load_images_into_struct(macro);
    printf("rendering minimap...\n");
	while (x < macro->map->h_map)
	{
		y = 0;
		while (y < macro->map->w_map)
		{
			render_block(macro, macro->minimap->background, y, x);
			if (macro->map->map[x][y] == '1')
				render_block(macro, macro->minimap->wall,  y, x);
			y += 1;
		}
		x += 1;
	}
	render_block(macro, macro->minimap->player, macro->start_x, macro->start_y);
	//draw_cone(macro);
}
