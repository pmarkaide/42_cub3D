/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:22:37 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/27 02:05:37 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

char	*get_skipped(char *line)
{
	char	*skipped;

	skipped = ft_skipws(line);
	skipped = ft_skipws(skipped + 1);
	return (skipped);
}

void	exit_malloc(t_macro *m)
{
	ft_printf(2, "Error\nMalloc failed\n");
	free_all(m);
}
