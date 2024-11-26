/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:05:20 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/26 21:38:36 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	validate_colors(t_macro *m)
{
	int	i;
	int	*f;
	int	*c;

	f = m->map->f;
	c = m->map->c;
	i = 0;
	while (i < 3)
	{
		if (f[i] < 0 || f[i] > 255)
		{
			ft_printf(2, "Error\nFloor color value %d out of range\n", f[i]);
			free_macro(m);
		}
		if (c[i] < 0 || c[i] > 255)
		{
			ft_printf(2, "Error\nCeiling color value %d out of range\n", c[i]);
			free_macro(m);
		}
		i++;
	}
	return ;
}

static void	validate_textures_files(t_macro *m, int mlx)
{
	if (mlx == 0)
	{
		check_file_contents(m->map->no, m);
		check_file_contents(m->map->so, m);
		check_file_contents(m->map->we, m);
		check_file_contents(m->map->ea, m);
	}
}

void create_buffer_zone(t_macro *m)
{
    int i, j;
    int new_height = m->map->h_map + 12; // 6 rows at the top and 6 at the bottom
    int new_width = m->map->w_map + 12;  // 6 columns on the left and 6 on the right

    // Allocate memory for the new buff map with additional rows and columns
    m->map->buff = (char **)malloc((new_height + 1) * sizeof(char *));
    i = 0;
    while (i < new_height)
    {
        m->map->buff[i] = (char *)malloc((new_width + 1) * sizeof(char));
        i++;
    }
    m->map->buff[new_height] = NULL; // Set the last string to NULL

    // Initialize the buffer zone with '1' in the first and last row and column, and '0' in the rest
    i = 0;
    while (i < new_height)
    {
        j = 0;
        while (j < new_width)
        {
            if (i == 0 || i == new_height - 1 || j == 0 || j == new_width - 1)
            {
                m->map->buff[i][j] = '1';
            }
            else
            {
                m->map->buff[i][j] = '0';
            }
            j++;
        }
        i++;
    }

    // Copy the existing map data into the new buff map
    i = 0;
    while (i < m->map->h_map)
    {
        j = 0;
        while (j < m->map->w_map)
        {
            m->map->buff[i + 6][j + 6] = m->map->grid[i][j];
            j++;
        }
        i++;
    }
    m->map->h_map = new_height;
    m->map->w_map = new_width;
}

void	validation(t_macro *m)
{
	validate_textures_files(m, 0);
	validate_colors(m);
	validate_map(m);
	substitute_spaces_with_zeros(m);
    create_buffer_zone(m);
}
