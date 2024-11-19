/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:46:43 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 14:03:57 by pmarkaid         ###   ########.fr       */
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
	char		orientation;
	int			start_x;
	int			start_y;
}				t_map;

typedef struct s_images
{
	mlx_image_t	*mini_i;
	mlx_image_t	*scene_i;
	mlx_image_t	*wall;
	mlx_image_t	*background;
	mlx_image_t	*player;
}				t_images;

typedef struct s_keys
{
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_left;
	int	key_right;
}				t_keys;

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int32_t	wall_color;
	int32_t	floor;
	int32_t	ceiling;
	float	play_view;
	double	play_angle;
	int		pos_pl_x;
	int		pos_pl_y;
	double	distance;
}				t_raycast;

typedef struct s_macro
{
	mlx_t		*mlx_cub;
	t_map		*map;
	t_images	*images;
	t_keys		*keys;
	t_raycast	*raycast;
	int			width;
	int			height;
}				t_macro;

t_macro			*init_macro(t_macro *m);
void			free_and_exit(t_macro *m);
void			free_map(t_macro *m);
void			free_macro(t_macro *m);
int				validation(t_macro *m);
int				validate_map(t_macro *m);
int				check_file_contents(char *file);
void			clean_trailing_char(char *str, const char *set);
int				save_texture_path(char **texture, char *path);
int				parse_line(char *line, t_macro *m, int section, t_list **head);
void			read_input(char *file, t_macro *m);
void			calculate_map_dimensions(t_macro *m);
void			quit_hook(void *param);
void			release_all(mlx_key_data_t keydata, t_macro *m);
void			ft_hook(mlx_key_data_t keydata, void *param);
void			load_images_into_struct(t_macro *m);
void			unload_images_from_struct(t_macro *m);
void			initialize_vision_ray(t_macro *m, int x, double *ray_dir_x, double *ray_dir_y);
void			calculate_ray_steps(t_macro *m, double ray_dir_x, double ray_dir_y);
void			draw_ray(t_macro *m, float ray_length, double ray_dir_x, double ray_dir_y);
void			draw_vision_cone(t_macro *m);
void			draw_minimap(t_macro *m);
void			print_map_struct(t_map *map);
void			ft_hook(mlx_key_data_t keydata, void *param);
void			load_game(void *param);
void			load_player(t_macro *m);
void			player_in_map(t_macro *m);
void			load_map(t_macro *m);
void			calculate_wall_distance(t_macro *m);
void			draw_wall_slice(t_macro *m, int x);
void			paint_wall(t_macro *m);
void			paint_background(t_macro *m);
void			calculate_ray_direction(t_macro *m, int x);
void			calculate_step_and_side_dist(t_macro *m);
void			perform_dda(t_macro *m);
void			load_player(t_macro *m);
void			player_in_map(t_macro *m);
void			load_map(t_macro *m);
void			correct_player_pos_in_edge(t_macro *m);
int32_t			mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y);
void			put_img2img(mlx_image_t *dst, mlx_image_t *src, int x, int y);
int				get_rgba(int r, int g, int b, int a);
void			move_wsda(t_macro *m);
void			move_rotate(t_macro *m);
void			stop_at_wall(t_macro *m, int x, int y);

#endif
