/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:08:42 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/04 11:54:55 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "MLX42.h"    // mlx42
# include <fcntl.h>    // open
# include <stdio.h>    // printf, perror
# include <stdlib.h>   // malloc, free, exit
# include <string.h>   // strerror
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // close, read, write
# include <errno.h>    // errno

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

#endif

t_macro	*init_macro(t_macro *macro);
void	validate_map_file(char *file, t_macro *macro);
void	free_and_exit(t_macro *macro);




/* _utils */
void	print_map_struct(t_map *map);