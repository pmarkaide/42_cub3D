/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:08:42 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/04 16:40:34 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "MLX42.h"    // mlx42
# include <errno.h>    // errno
# include <fcntl.h>    // open
# include <stdio.h>    // printf, perror
# include <stdlib.h>   // malloc, free, exit
# include <string.h>   // strerror
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // close, read, write

# define WIDTH 512
# define HEIGHT 512

typedef struct s_mlx
{
	mlx_image_t	*img;
	mlx_t		*mlx_cub;
}				t_mlx;

typedef struct s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			f[3];
	int			c[3];
	char		**map;
	int			w_map;
	int			h_map;
}				t_map;

typedef struct s_macro
{
	t_map		*map;
	int			play_x;
	int			play_y;
	char		play_facing;
	t_mlx		*m_mlx;
}				t_macro;

t_macro			*init_macro(t_macro *macro);
void			free_and_exit(t_macro *macro);
void			free_map(t_macro *macro);
void			free_macro(t_macro *macro);
void			print_map_struct(t_map *map);
int				validation(t_macro *macro);
int				validate_map(t_macro *macro);
int				check_file_contents(char *file);
void			clean_trailing_char(char *str, const char *set);
int				save_texture_path(char **texture, char *path);
int				parse_line(char *line, t_macro *macro, int section, t_list **head);
void			read_input(char *file, t_macro *macro);
void			calculate_map_dimensions(t_macro *macro);

/* _utils */
void			print_map_struct(t_map *map);

#endif
