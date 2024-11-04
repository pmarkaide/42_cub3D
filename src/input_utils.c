/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:12:51 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/04 12:21:39 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int check_file_contents(char *file)
{
	int fd;
	char buffer[1];
	ssize_t bytes_read;

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
		ft_printf(2, "Error\nFile %s is empty or unreadable: %s\n", file, strerror(errno));
		return (1);
	}
	return (0);
}

char *clean_trailingws(char *line)
{
    char *end;
    
    end = line + ft_strlen(line) - 1;
    while (end > line && (*end == ' ' || *end == '\n' || *end == '\t'))
    {
        *end = '\0';
        end--;
    }
    return (line);
}

int save_texture_path(char **texture, char *path)
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
