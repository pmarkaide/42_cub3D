/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:10:49 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/21 17:00:28 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_position(t_macro *m, char** visited, size_t x, size_t y)
{
	if (x >= m->map->h_map)
		return (0);
	if (y >= m->map->w_map)
		return (0);
	if (m->map->grid[x][y] == '1')
		return (0);
	if (visited[x][y])
		return (0);
	return (1);
}

void	flood_fill(t_macro *m, char** visited, size_t x, size_t y)
{
	if (!is_valid_position(m, visited, x, y))
		return;
	visited[x][y] = 1;
	 if (x > 0)
        flood_fill(m, visited, x - 1, y);
    if (x < m->map->h_map - 1)
        flood_fill(m, visited, x + 1, y);
    if (y > 0)
        flood_fill(m, visited, x, y - 1);
    if (y < m->map->w_map - 1)
        flood_fill(m, visited, x, y + 1);
}

char	**create_visited_array(size_t height, size_t width)
{
	char	**visited;
	size_t	i;
	size_t	j;

	visited = (char **)malloc(sizeof(char *) * height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = (char *)malloc(sizeof(char) * width);
		if (!visited[i])
		{
			while (i > 0)
				free(visited[--i]);
			free(visited);
			return (NULL);
		}
		j = 0;
		while (j < width)
			visited[i][j++] = 0;
		i++;
	}
	return (visited);
}

void	free_visited_array(char **visited, size_t height)
{
	size_t	i;

	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
}

void	print_arrays(t_macro *m, char **visited)
{
	size_t	i;
	size_t	j;

	ft_printf(1, "Grid:\n");
	for (i = 0; i < m->map->h_map; i++)
	{
		for (j = 0; j < m->map->w_map; j++)
			ft_printf(1, "%c ", m->map->grid[i][j]);
		ft_printf(1, "\n");
	}
	ft_printf(1, "\nVisited:\n");
	for (i = 0; i < m->map->h_map; i++)
	{
		for (j = 0; j < m->map->w_map; j++)
			ft_printf(1, "%d ", visited[i][j]);
		ft_printf(1, "\n");
	}
}

int	check_path(t_macro *m, char **visited)
{
	size_t	i;
	size_t	j;
	char	**grid;

	grid = m->map->grid;
	m->map->grid[m->map->start_y][m->map->start_x] = '0';
	flood_fill(m, visited, m->map->start_y, m->map->start_x);
	print_arrays(m, visited);
	i = 0;
	while (i < m->map->h_map)
	{
		j = 0;
		while (j < m->map->w_map)
		{
			if (grid[i][j] == '1' || grid[i][j] == '0')
			{
				if (!visited[i][j])
				{
					ft_printf(2, "Error\nMaps with islands not accepted\n");
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}
