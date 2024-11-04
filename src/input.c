/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:57:04 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/04 12:29:46 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static int	eval_file(char *file, char *ext)
{
	char	*dot;

	if(ft_strcmp(ext,".cub") == 0)
	{
		dot = ft_strrchr(file, '.');
		if(dot == NULL || (dot != NULL && ft_strcmp(dot, ".cub")))
		{
			ft_printf(2, "Error\nWrong file extension\n");
			return (1);
		}
	}
	return check_file_contents(file);
}

static int detect_section(char *line)
{
	char *skipped;
	int section;

	skipped = ft_skipws(line);
	if (*skipped == '\0' || *skipped == '\n')
		section = 0;
	else if(ft_strncmp(skipped, "NO ",3) == 0)
		section= 1;
	else if(ft_strncmp(skipped, "SO ",3) == 0)
		section= 1;
	else if(ft_strncmp(skipped, "WE ",3) == 0)
		section= 1;
	else if(ft_strncmp(skipped, "EA ",3) == 0)
		section= 1;
	else if(ft_strncmp(skipped, "F ",2) == 0)
		section= 2;
	else if(ft_strncmp(skipped, "C ",2) == 0)
		section= 2;
	else
		section= 3;
	return(section);
}

static int read_file(char *file, t_macro *macro)
{
	char *line;
	int fd;
	int section;
	t_list *head = NULL;
	
	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		section = detect_section(line);
		if (parse_line(line, macro, section, &head))
		{
			close(fd);
			free(line);
			ft_lstclear(&head, free);
			return (1);
		}
		free(line);
	}
	close(fd);
	macro->map->map = ft_lst_to_array(&head);
	ft_lstclear(&head, free); 
	return (0);
}

void	read_input(char *file, t_macro *macro)
{
	if (eval_file(file, ".cub"))
		free_and_exit(macro);
	if (read_file(file, macro))
		free_and_exit(macro);
	print_map_struct(macro->map);
	if (validation(macro))
		free_and_exit(macro);
}