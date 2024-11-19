/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:12:51 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 12:23:29 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_map_dimensions(t_macro *m)
{
	int		height;
	int		width;
	int		current_width;
	char	**map;

	height = 0;
	width = 0;
	map = m->map->grid;
	while (map[height])
	{
		current_width = ft_strlen(map[height]);
		if (current_width > width)
			width = current_width;
		height++;
	}
	m->map->w_map = width;
	m->map->h_map = height;
}

int	check_file_contents(char *file)
{
	int		fd;
	char	buffer[1];
	ssize_t	bytes_read;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(2, "LOL\nCannot open file %s:%s\n", file, strerror(errno));
		return (1);
	}
	bytes_read = read(fd, buffer, 1);
	close(fd);
	if (bytes_read <= 0)
	{
		ft_printf(2, "Error\nFile %s is empty or unreadable: %s\n", file,
			strerror(errno));
		return (1);
	}
	return (0);
}

void	clean_trailing_char(char *str, const char *set)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && ft_strchr(set, str[len - 1]))
	{
		str[len - 1] = '\0';
		len--;
	}
}

int	save_texture_path(char **texture, char *path)
{
	if (*texture != NULL)
	{
		ft_printf(2, "Error\nDuplicate texture path\n");
		return (1);
	}
	*texture = ft_strdup(path);
	if (*texture == NULL)
	{
		ft_printf(2, "Error\nMemory allocation failed\n");
		return (1);
	}
	return (0);
}
