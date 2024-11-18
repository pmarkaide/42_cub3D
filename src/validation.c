/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:05:20 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/18 15:49:12 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	validate_textures(t_macro *macro)
{
	if (check_file_contents(macro->map->no))
		return (1);
	if (check_file_contents(macro->map->so))
		return (1);
	if (check_file_contents(macro->map->we))
		return (1);
	if (check_file_contents(macro->map->ea))
		return (1);
	return (0);
}

static int	validate_colors(int *f, int *c)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (f[i] < 0 || f[i] > 255)
		{
			ft_printf(2, "Error\nFloor color value %d out of range\n", f[i]);
			return (1);
		}
		if (c[i] < 0 || c[i] > 255)
		{
			ft_printf(2, "Error\nCeiling color value %d out of range\n", c[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	fill_with_spaces(char **map, size_t width)
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

int	validation(t_macro *macro)
{
	if (validate_textures(macro))
		return (1);
	if (validate_colors(macro->map->f, macro->map->c))
		return (1);
	if (validate_map(macro))
		return (1);
	fill_with_spaces(macro->map->grid, macro->map->w_map);
	return (0);
}
