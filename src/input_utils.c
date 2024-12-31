/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:12:51 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/12/27 20:51:42 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Checks if the file can be readed and is not empty.
 * 
 * @param file The file path.
 * @param m Pointer to the macro structure.
 * @return 0 if the file is valid, 1 otherwise.
 */
int	check_file_contents(char *file, t_macro *m)
{
	int		fd;
	char	buffer[1];
	ssize_t	bytes_read;

	(void)m;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(2, "Error\n");
		ft_printf(2, "Cannot open file %s: %s\n", file, strerror(errno));
		return (1);
	}
	bytes_read = read(fd, buffer, 1);
	close(fd);
	if (bytes_read <= 0)
	{
		ft_printf(2, "Error\nFile %s is empty or unreadable\n", file);
		return (1);
	}
	return (0);
}

/**
 * Removes trailing characters from the string.
 * 
 * @param str The input string.
 * @param set The set of characters to be removed.
 */
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

/**
 * Store the texture path from the input string.
 * 
 * @param texture Pointer to the texture path.
 * @param path The input string containing the texture path.
 * @return 0 if saving is successful, 1 otherwise.
 */
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

/**
 * Checks if the map line contains valid characters.
 * 
 * @param line The input string.
 * @return 1 if the line is valid, 0 otherwise.
 */
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

/**
 * Finishes reading the file when exited prematurely due to parsing errors.
 * 
 * This avoid get_next_line leaks.
 * 
 * @param fd The file descriptor.
 * @param line The input string.
 */
void	finish_reading_the_file(int fd, char *line)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
