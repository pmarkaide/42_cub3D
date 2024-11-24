/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:57:04 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/24 13:03:14 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	eval_extension(char *file, char *ext, t_macro *m)
{
	char	*dot;

	if (ft_strcmp(ext, ".cub") == 0)
	{
		dot = ft_strrchr(file, '.');
		if (dot == NULL || (dot != NULL && ft_strcmp(dot, ".cub")))
		{
			ft_printf(2, "Error\nWrong file extension\n");
			free_macro(m);
		}
	}
	return (0);
}

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
			free(line);
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

static void	read_file(char *file, t_macro *m)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		ft_printf(2, "Error\nEmpty file\n");
		close(fd);
		free_macro(m);
	}
	if (handle_lines(m, fd, line))
	{
		close(fd);
		free_macro(m);
	}
	close(fd);
}

void	read_input(char *file, t_macro *m)
{
	eval_extension(file, ".cub", m);
	check_file_contents(file, m);
	read_file(file, m);
	validation(m);
	print_map_struct(m->map);
}
