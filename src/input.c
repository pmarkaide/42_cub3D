/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:57:04 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 13:00:37 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	eval_file(char *file, char *ext)
{
	char	*dot;

	if (ft_strcmp(ext, ".cub") == 0)
	{
		dot = ft_strrchr(file, '.');
		if (dot == NULL || (dot != NULL && ft_strcmp(dot, ".cub")))
		{
			ft_printf(2, "Error\nWrong file extension\n");
			return (1);
		}
	}
	return (check_file_contents(file));
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

static char	**handle_lines(t_macro *m, int fd)
{
	char	*line;
	int		section;
	t_list	*head;

	head = NULL;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	while (line)
	{
		section = detect_section(line);
		if (parse_line(line, m, section, &head))
		{
			free(line);
			ft_lstclear(&head, free);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	m->map->grid = ft_lst_to_array(&head);
	ft_lstclear(&head, free);
	return (m->map->grid);
}

static int	read_file(char *file, t_macro *m)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(2, "Error\nFailed to open file\n");
		return (1);
	}
	if (!handle_lines(m, fd))
	{
		close(fd);
		ft_printf(2, "Error\nFailed to parse file\n");
		return (1);
	}
	close(fd);
	return (0);
}

void	read_input(char *file, t_macro *m)
{
	if (eval_file(file, ".cub"))
		free_and_exit(m);
	if (read_file(file, m))
		free_and_exit(m);
	if (validation(m))
		free_and_exit(m);
	print_map_struct(m->map);
}
