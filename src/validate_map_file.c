/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:05:20 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/04 09:21:08 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int check_file_contents(char *file)
{
	int fd;
	char buffer[1];
	ssize_t bytes_read;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(2, "Error\nCannot open file %s\n", file);
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

static int set_texture_path(char **texture, char *path)
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

static int parse_textures(char *line, t_macro *macro)
{
	int err = 0;
	char *skipped = ft_skipws(line);
	char *path = ft_skipws(skipped + 2);

	if (ft_strncmp(skipped, "NO ", 3) == 0)
		err = set_texture_path(&(macro->map->no), path);
	else if (ft_strncmp(skipped, "SO ", 3) == 0)
		err = set_texture_path(&(macro->map->so), path);
	else if (ft_strncmp(skipped, "WE ", 3) == 0)
		err = set_texture_path(&(macro->map->we), path);
	else if (ft_strncmp(skipped, "EA ", 3) == 0)
		err = set_texture_path(&(macro->map->ea), path);
	return err;
}
static  int parse_colors(char *line, t_macro *macro)
{
	char *skipped;
	int i;

	i = -1;
	skipped = ft_skipws(line);
	skipped = ft_skipws(skipped + 1);
	while(++i < 3)
	{
		if(ft_skipws(line)[0] == 'F')
			macro->map->f[i] = ft_atoi(skipped);
		else if(ft_skipws(line)[0]  == 'C')
			macro->map->c[i] = ft_atoi(skipped);
		skipped = ft_strchr(skipped, ',');
		if(skipped)
			skipped++;
	}
	return(0);
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

static int parse_map(char *line, t_list **head)
{
	t_list *new;

	new = ft_lstnew(ft_strdup(line));
	if (!new)
		return (1);
	ft_lstadd_back(head, new);
	return (0);
}

static int premap_ready(t_macro *macro)
{
	int i = 0;

	if (macro->map->no == NULL || macro->map->so == NULL ||
		macro->map->we == NULL || macro->map->ea == NULL)
		return (0);
	while (i < 3)
	{
		if (macro->map->f[i] == -1 || macro->map->c[i] == -1)
			return (0);
		i++;
	}
	return (1);
}

static int parse_line(char *line, t_macro *macro, int section, t_list **head)
{
	int err;

	err = 0;
	if(section == 0)
		return(0);
	if(section == 1)
		err = parse_textures(line, macro);
	if(section == 2)
		err = parse_colors(line, macro);
	if(section == 3)
	{
		if (!premap_ready(macro))
		{
			ft_printf(2, "Error\nMap section found before textures and colors are fully defined\n");
			return (1);
		}
		err = parse_map(line, head);
	}
	return(err);
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

static int validate_textures(t_macro *macro)
{
	if (check_file_contents(macro->map->no))
		return (1);
	if (check_file_contents(macro->map->so))
		return (1);
	if (check_file_contents(macro->map->we))
		return (1);
	if (check_file_contents(macro->map->ea))
		return (1);
	return (0);
}

static int validate_colors(int *f, int *c)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (f[i] < 0 || f[i] > 255)
		{
			ft_printf(2, "Error\nFloor color value %d out of range\n", f[i]);
			return (1);
		}
		if (c[i] < 0 || c[i] > 255)
		{
			ft_printf(2, "Error\nCeiling color value %d out of range\n", c[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int is_valid_map_char(char **map)
{
	int i, j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (strchr("10NSWE ", map[i][j]) == NULL)
			{
				ft_printf(2, "Error\nInvalid character '%c' in map\n", map[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static void calculate_map_dimensions(t_macro *macro)
{
	int height = 0;
	int width = 0;
	int current_width;
	char **map = macro->map->map;

	while (map[height])
	{
		current_width = ft_strlen(map[height]);
		if (current_width > width)
			width = current_width;
		height++;
	}
	macro->map->w_map = width;
	macro->map->h_map = height;
}

static int check_first_last_rows(t_macro *macro)
{
	int j = 0;
	char **map = macro->map->map;
	int width = macro->map->w_map;

	while (j < width)
	{
		if (map[0][j] == '0' || map[0][j] == ' ')
			return (0);
		if (map[macro->map->h_map - 1][j] == '0' || map[macro->map->h_map - 1][j] == ' ')
			return (0);
		j++;
	}
	return (1);
}

static int check_edges(char **map, int height)
{
	int i = 1;
	int len;

	while (i < height - 1)
	{
		len = ft_strlen(map[i]);
		if (map[i][0] == '0' || map[i][len - 1] == '0' ||
			map[i][0] == ' ' || map[i][len - 1] == ' ')
			return (0);
		i++;
	}
	return (1);
}

static int check_spaces(char **map, int height)
{
	int i = 1;
	int j;

	while (i < height - 1)
	{
		j = 1;
		while (map[i][j + 1])
		{
			if (map[i][j] == ' ' && (map[i][j - 1] != '1' || map[i][j + 1] != '1'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int is_valid_map_structure(t_macro *macro)
{
	char **map = macro->map->map;

	if (!check_first_last_rows(macro))
		return (0);
	if (!check_edges(map, macro->map->h_map))
		return (0);
	if (!check_spaces(map, macro->map->h_map))
		return (0);
	return (1);
}

static int evaluate_map(t_macro *macro)
{
	calculate_map_dimensions(macro);

	if (!is_valid_map_char(macro->map->map))
		return (1);
	if (!is_valid_map_structure(macro))
	{
		ft_printf(2, "Error\nInvalid map structure\n");
		return (1);
	}
	return (0);
}

int validate_contents(t_macro *macro)
{
	if (validate_textures(macro))
		return (1);
	if (validate_colors(macro->map->f, macro->map->c))
		return (1);
	if (evaluate_map(macro))
		return (1);
	return (0);
}

void	validate_map_file(char *file, t_macro *macro)
{
	if (eval_file(file, ".cub"))
		free_and_exit(macro);
	if (read_file(file, macro))
		free_and_exit(macro);
	print_map_struct(macro->map);
	if (validate_contents(macro))
		free_and_exit(macro);
}
