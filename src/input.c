/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:57:04 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/12/27 21:00:07 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Evaluates the file extension to ensure it is a .cub file.
 * 
 * @param file The file path.
 * @param m Pointer to the macro structure.
 * @return 0 if the extension is valid, 1 otherwise.
 */
static int	eval_extension(char *file, t_macro *m)
{
	char	*dot;
	int		err;

	dot = ft_strrchr(file, '.');
	err = 0;
	if (dot == NULL || ft_strcmp(dot, ".cub"))
		err = 1;
	else if (dot == file || *(dot - 1) == '/')
		err = 1;
	if (err)
	{
		ft_printf(2, "Error\nWrong file extension\n");
		free_macro(m);
		return (1);
	}
	return (0);
}

/**
 * Detects the section type of the input line based on the leading key value.
 * 
 * @param line The input string.
 * @return The section type as an integer.
 */
static int	detect_section(char *line)
{
	char	*skipped;
	int		section;

	skipped = ft_skipws(line);
	if (*skipped == '\0' || *skipped == '\n')
		section = 0;
	else if (ft_strncmp(skipped, "NO ", 3) == 0)
		section = 1;
	else if (ft_strncmp(skipped, "SO ", 3) == 0)
		section = 1;
	else if (ft_strncmp(skipped, "WE ", 3) == 0)
		section = 1;
	else if (ft_strncmp(skipped, "EA ", 3) == 0)
		section = 1;
	else if (ft_strncmp(skipped, "F ", 2) == 0)
		section = 2;
	else if (ft_strncmp(skipped, "C ", 2) == 0)
		section = 2;
	else
		section = 3;
	return (section);
}

/**
 * Read a line from the map file and detect which section corresponds to.
 * Based on that, it calls the appropiate function that parse this section line.
 * 
 * @param m Pointer to the macro structure.
 * @param fd The file descriptor.
 * @param line The input string.
 * @return 0 if parsing is successful, 1 otherwise.
 */
static int	handle_lines(t_macro *m, int fd, char *line)
{
	int		section;
	t_list	*head;

	head = NULL;
	while (line)
	{
		section = detect_section(line);
		if (parse_line(line, m, section, &head))
		{
			finish_reading_the_file(fd, line);
			ft_lstclear(&head, free);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	m->map->grid = ft_lst_to_array(&head);
	if (m->map->grid == NULL || m->map->grid[0] == NULL)
	{
		ft_printf(2, "Error\nEmpty map grid\n");
		ft_lstclear(&head, free);
		return (1);
	}
	ft_lstclear(&head, free);
	return (0);
}

/**
 * Reads the input file and processes its contents.
 * The main function is handle_lines.
 * This is just a caller due to line liminations.
 * 
 * @param file The file path.
 * @param m Pointer to the macro structure.
 * @return 0 if reading is successful, 1 otherwise.
 */
static int	read_file(char *file, t_macro *m)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		ft_printf(2, "Error\nEmpty file\n");
		close(fd);
		return (1);
	}
	if (handle_lines(m, fd, line))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * Reads and validates the input file.
 * 
 * A positive result will store all the map file info into the macro struct.
 * 
 * @param file The file path.
 * @param m Pointer to the macro structure.
 * @return 0 if the input is valid, 1 otherwise.
 */
int	read_input(char *file, t_macro *m)
{
	if (eval_extension(file, m))
		return (1);
	if (check_file_contents(file, m))
		return (1);
	if (read_file(file, m))
		return (1);
	if (validation(m))
		return (1);
	return (0);
}
