/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:46:43 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/18 15:48:48 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "MLX42.h" // mlx42
# include <errno.h> // errno
# include <fcntl.h> // open
# include <math.h>
# include <stdbool.h>
# include <stdio.h>    // printf, perror
# include <stdlib.h>   // malloc, free, exit
# include <string.h>   // strerror
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // close, read, write

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define WIDTH 512
# define HEIGHT 512
# define BLOCK 32      // size of each block
# define ANGLE_VIEW 60 // Angle View for the Player
# define RATIO_SCREEN 0.75
# define ROT_SPEED 0.05
# define WALK_SPEED 5

typedef struct s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			f[3];
	int			c[3];
	char		**grid;
	size_t		w_map;
	size_t		h_map;
}				t_map;

typedef struct s_minimap
{
	mlx_image_t	*wall;
	mlx_image_t	*background;
	mlx_image_t	*player;
	int			vision_distance;
	float		vision_angle;
}				t_minimap;
typedef struct s_macro
{
	t_map		*map;
	t_minimap	*minimap;
	mlx_image_t	*mini_i;
	mlx_image_t	*scene_i;
	int			play_x;
	int			play_y;
	int			width;
	int			height;
	char		orientation;
	int32_t		floor;
	int32_t		ceiling;
	int32_t		wall;
	int			start_x;
	int			start_y;
	int			pos_pl_x;
	int			pos_pl_y;
	float		play_view;
	double		play_angle;
	char		play_facing;
	int			w_map;
	int			h_map;
	double		distance;
	double		line_angle;
	mlx_image_t	*img;
	mlx_t		*mlx_cub;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int32_t		wall_color;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
}				t_macro;

t_macro			*init_macro(t_macro *macro);
void			free_and_exit(t_macro *macro);
void			free_map(t_macro *macro);
void			free_macro(t_macro *macro);
int				validation(t_macro *macro);
int				validate_map(t_macro *macro);
int				check_file_contents(char *file);
void			clean_trailing_char(char *str, const char *set);
int				save_texture_path(char **texture, char *path);
int				parse_line(char *line, t_macro *macro, int section,
					t_list **head);
void			read_input(char *file, t_macro *macro);
void			calculate_map_dimensions(t_macro *macro);
void			quit_hook(void *param);
void			load_images_into_struct(t_macro *macro);
void			unload_images_from_struct(t_macro *macro);
void			draw_minimap(t_macro *macro);
void			init_mini_image(t_macro *macro);

/* _utils */
void			print_map_struct(t_map *map);

/* Merged functions */
// char** 	parse_map(const char* filename, int* rows, int* cols);
void			ft_hook(mlx_key_data_t keydata, void *param);
void			load_game(void *param);
void			print_map(t_macro *macro);
void			calculate_wall_distance(t_macro *macro);
void			draw_wall_slice(t_macro *macro, int x);
void			paint_wall(t_macro *macro);
void			paint_background(t_macro *macro);
void			calculate_ray_direction(t_macro *macro, int x);
void			calculate_step_and_side_dist(t_macro *macro);
void			perform_dda(t_macro *macro);
void			load_player(t_macro *macro);
void			player_in_map(t_macro *macro);
void			load_map(t_macro *macro);
int32_t			mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y);
void			put_img2img(mlx_image_t *dst, mlx_image_t *src, int x, int y);
int				get_rgba(int r, int g, int b, int a);

#endif
