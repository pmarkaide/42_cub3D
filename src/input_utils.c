/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:12:51 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/25 23:36:21 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_file_contents(char *file, t_macro *m)
{
	int		fd;
	char	buffer[1];
	ssize_t	bytes_read;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(2, "Error\n");
		ft_printf(2, "Cannot open file %s: %s\n", file, strerror(errno));
		free_macro(m);
	}
	bytes_read = read(fd, buffer, 1);
	close(fd);
	if (bytes_read <= 0)
	{
		ft_printf(2, "Error\nFile %s is empty or unreadable\n", file);
		free_macro(m);
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
	char	*temp;
	char	*clean;

	if (*texture != NULL)
	{
		ft_printf(2, "Error\nDuplicate texture path\n");
		return (1);
	}
	clean = ft_strtrim(path, " \t\n");
	if (!clean || ft_strchr(clean, ' ') || ft_strlen(clean) == 0)
	{
		ft_printf(2, "Error\nInvalid texture path\n");
		free(clean);
		return (1);
	}
	temp = ft_strdup(clean);
	free(clean);
	if (temp == NULL)
	{
		ft_printf(2, "Error\nMemory allocation failed\n");
		return (1);
	}
	*texture = temp;
	return (0);
}

int	map_line_is_correct(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (ft_strchr("10NSWE \n", line[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}
