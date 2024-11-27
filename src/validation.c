/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:05:20 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/27 02:07:10 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	validate_colors(t_macro *m)
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

static int	validate_textures_files(t_macro *m, int mlx)
{
	if (mlx == 0)
	{
		if (check_file_contents(m->map->no, m))
			return (1);
		if (check_file_contents(m->map->so, m))
			return (1);
		if (check_file_contents(m->map->we, m))
			return (1);
		if (check_file_contents(m->map->ea, m))
			return (1);
	}
	return (0);
}

int	validation(t_macro *m)
{
	if (validate_textures_files(m, 0))
		return (1);
	if (validate_colors(m))
		return (1);
	validate_map(m);
	substitute_spaces_with_zeros(m);
	create_buffer_zone(m);
	return (0);
}
