/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:10:49 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/25 23:35:24 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_position(t_macro *m, char **visited, int x, int y)
{
	if (x >= m->map->h_map)
		return (0);
	if (y >= m->map->w_map)
		return (0);
	if (m->map->grid[x][y] == ' ')
		return (0);
	if (visited[x][y])
		return (0);
	return (1);
}

void	flood_fill(t_macro *m, char **visited, int x, int y)
{
	if (!is_valid_position(m, visited, x, y))
		return ;
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

char	**create_visited_array(int height, int width)
{
	char	**visited;
	int		i;
	int		j;

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

void	free_visited_array(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
}

int	check_path(t_macro *m, char **visited)
{
	int		i;
	int		j;
	char	**grid;

	grid = m->map->grid;
	flood_fill(m, visited, m->map->start_y, m->map->start_x);
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
