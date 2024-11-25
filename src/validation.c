/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:05:20 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/25 23:38:29 by dbejar-s         ###   ########.fr       */
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

void	validation(t_macro *m)
{
	validate_textures_files(m, 0);
	validate_colors(m);
	validate_map(m);
	substitute_spaces_with_zeros(m);
}
