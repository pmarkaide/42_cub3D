/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:05:20 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/21 13:51:28 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	validate_textures(t_macro *m)
{
	if (check_file_contents(m->map->no, m))
	{
		free_macro(m);
		return (1);
	}
	if (check_file_contents(m->map->so, m))
	{
		free_macro(m);
		return (1);
	}
	if (check_file_contents(m->map->we, m))
	{
		free_macro(m);
		return (1);
	}
	if (check_file_contents(m->map->ea, m))
	{
		free_macro(m);
		return (1);
	}
	return (0);
}

static int	validate_colors(int *f, int *c, t_macro *m)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (f[i] < 0 || f[i] > 255)
		{
			ft_printf(2, "Error\nFloor color value %d out of range\n", f[i]);
			free_macro(m);
			return (1);
		}
		if (c[i] < 0 || c[i] > 255)
		{
			ft_printf(2, "Error\nCeiling color value %d out of range\n", c[i]);
			free_macro(m);
			return (1);
		}
		i++;
	}
	return (0);
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

int	validation(t_macro *m)
{
	if (!m->map->grid)
	{
		ft_printf(2, "Error\nMap malloc failed\n");
		free_macro(m);
	}
	if (validate_textures(m))
		return (1);
	if (validate_colors(m->map->f, m->map->c, m))
		return (1);
	calculate_map_dimensions(m);
	fill_with_spaces(m->map->grid, m->map->w_map);
	if (validate_map(m))
		return (1);
	return (0);
}
