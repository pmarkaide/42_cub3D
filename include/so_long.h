/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:20:20 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/05 15:11:50 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "../lib/libft/libft.h"
#include "colors.h"

#define BLOCK_SIZE 32

typedef struct s_map
{
	char		*map_str;
	char		**map;
	size_t		rows;
	size_t		cols;
	size_t		coins;
	size_t		start_x;
	size_t		start_y;
	size_t		exit_x;
	size_t		exit_y;
	size_t		**visited;
}				t_map;

typedef struct s_data
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*coin;
	mlx_image_t	*exit;
	mlx_image_t	*background;
	size_t		height;
	size_t		width;
	size_t		pos_x;
	size_t		pos_y;
	size_t		moves;
}				t_data;

void			map_is_valid(char *map_file, t_map *map);
void			free_map(t_map *data);
void			free_map_and_exit(t_map *map, char *error_msg);
void			free_game_and_bad_exit(t_data *data, char *error_msg);
void			free_game_and_good_exit(t_data *data);
int				error_1(const char *error_message);
char			*error_null(const char *error_message);
void			exit_1(const char *error_msg);
size_t			get_file_length_in_bytes(char *map_file);
void			file_is_valid(char *map_file);
void			check_path(t_map *data);
size_t			**allocate_2d_array(size_t rows, size_t cols);
int32_t			game_init(t_map map);
void			quit_hook(void *param);
void			player_hook(mlx_key_data_t keydata, t_data *data);
void			render_map(t_data *data);
void			new_player_image(t_data *data);
void			exit_hook(void *param);
void			load_images_into_struct(t_data *data, mlx_t *mlx);
mlx_image_t		*load_png_into_image(t_data *data, char *file);
size_t			count_rows_in_array(char **map);
char 			*read_whole_file(char *file);

