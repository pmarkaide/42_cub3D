/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:46:43 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/12/31 11:40:44 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "MLX42.h"  // mlx42
# include <errno.h>  // errno
# include <fcntl.h>  // open
# include <limits.h> // LONG_MAX, INT_MAX
# include <math.h>   // math
# include <stdlib.h> // malloc, free, exit
# include <string.h> // strerror
# include <unistd.h> // close, read, write

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define BLOCK 24          // size of each block
# define ANGLE_VIEW 60     // angle view for the player
# define ROT_SPEED 0.20    // rotation speed
# define WALK_SPEED 10     // walk speed
# define BUFF_AREA 2       // buffer distance
# define RATIO_SCREEN 0.75 // screen ratio

typedef struct s_text
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}					t_text;

typedef struct s_map
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				f[3];
	int				c[3];
	char			**grid;
	char			**buff;
	int				w_map;
	int				h_map;
	int				h_buff;
	int				w_buff;
	char			orientation;
	int				start_x;
	int				start_y;
}					t_map;

typedef struct s_keys
{
	int				key_w;
	int				key_a;
	int				key_s;
	int				key_d;
	int				key_left;
	int				key_right;
}					t_keys;

typedef struct s_ray
{
	int				index;
	double			distance;
	double			ray_dir_vx;
	double			ray_dir_vy;
	double			ray_dir_hx;
	double			ray_dir_hy;
	int				hit;
	int32_t			floor;
	int32_t			ceiling;
	float			play_view;
	double			play_angle;
	double			ray_angle;
	int				pos_pl_x;
	int				pos_pl_y;
}					t_ray;

typedef struct s_macro
{
	mlx_t			*mlx_cub;
	t_map			*map;
	mlx_image_t		*scene_i;
	t_keys			*keys;
	t_ray			*ray;
	t_text			*tex;
	int				width;
	int				height;
}					t_macro;

void				calculate_map_dimensions(t_macro *m);
int					check_file_contents(char *file, t_macro *m);
int					check_islands(t_macro *m, char **visited);
int					check_unique_starting_position(t_macro *m);
void				clean_trailing_char(char *str, const char *set);
void				create_buffer_zone(t_macro *m);
char				**create_visited_array(int height, int width);
int					cross_lines(double angle, float *crossed, float *step, int x_dda);
void				draw_wall(t_macro *m, int top_wall, int bottom, double wall_h);
void				do_wall(t_macro *m, int vertical);
void				fill_with_spaces(char **map, int width, t_macro *m);
void				finish_reading_the_file(int fd, char *line);
void				flood_fill(t_macro *m, char **visited, int x, int y);
void				free_all(t_macro *m);
void				free_macro(t_macro *m);
void				free_map(t_macro *m);
void				free_visited_array(char **visited, int height);
void				ft_hook(mlx_key_data_t keydata, void *param);
void				get_wsda(t_macro *m, double x, double y);
char				*get_skipped(char *line);
int					get_rgba(int r, int g, int b, int a);
mlx_texture_t		*get_texture(t_macro *m, int flag);
int					init_game(t_macro *m);
t_macro				*init_macro(t_macro *m);
int					is_valid_fc_format(char *line);
void				load_game(void *param);
void				load_map(t_macro *m);
void				load_player(t_macro *m);
void				map_chars_are_valid(t_macro *m);
int					map_line_is_correct(char *line);
int					make_color(int c);
void				mirror_vert(mlx_texture_t *texture, int left, int right);
void				move(t_macro *m);
void				move_wsda(t_macro *m, double x, double y);
float				normalize(float angle);
int					parse_color_values(char *skipped, int *color, int *err,t_macro *m);
int					parse_line(char *line, t_macro *m, int section,t_list **head);
void				player_in_map(t_macro *m);
int					radian_side(double angle, int side);
void				raycast(t_macro *m);
int					read_input(char *file, t_macro *m);
void				release_all(mlx_key_data_t keydata, t_macro *m);
int					save_texture_path(char **texture, char *path);
void				substitute_spaces_with_zeros(t_macro *m);
int					validation(t_macro *m);
void				validate_map(t_macro *m);
int					wall_hit(float x, float y, t_macro *m);
float				x_dda(t_macro *m, double angle, double dda);
double				x_off(mlx_texture_t *texture, t_macro *m);
float				y_dda(t_macro *m, double angle, double dda);

#endif
