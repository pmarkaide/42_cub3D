/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:05:20 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/21 17:01:20 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


static void	validate_colors(int *f, int *c, t_macro *m)
{
	int	i;

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
	return;
}

void	fill_with_spaces(char **map, size_t width)
{
	size_t	i;
	size_t	len;
	char	*new_line;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < width)
		{
			new_line = malloc(width + 1);
			if (!new_line)
				return ;
			ft_memcpy(new_line, map[i], len);
			ft_memset(new_line + len, ' ', width - len);
			new_line[width] = '\0';
			free(map[i]);
			map[i] = new_line;
		}
		i++;
	}
}

void substitute_spaces_with_zeros(char **grid, int width)
{
    int i = 0;
    while (grid[i] != NULL)
    {
        int j = 0;
        while (j < width)
        {
            if (grid[i][j] == ' ')
            {
                grid[i][j] = '0';
            }
            j++;
        }
        i++;
    }
}

void	validation(t_macro *m)
{
	char **visited;

	check_file_contents(m->map->no, m);
	check_file_contents(m->map->so, m);
	check_file_contents(m->map->we, m);
	check_file_contents(m->map->ea, m);
	validate_colors(m->map->f, m->map->c, m);
	calculate_map_dimensions(m);
	fill_with_spaces(m->map->grid, m->map->w_map);
	validate_map(m);
	//substitute_spaces_with_zeros(m->map->grid, m->map->w_map);
	visited = create_visited_array(m->map->h_map, m->map->w_map);
	if (!visited)
	{
		ft_printf(2, "Error\nMalloc failed\n");
		free_macro(m);
	}
	if (check_path(m, visited))
	{
		free_visited_array(visited, m->map->h_map);
		free_macro(m);
	}
	free_visited_array(visited, m->map->h_map);
}
