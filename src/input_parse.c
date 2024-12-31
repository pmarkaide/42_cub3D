/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:35 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/12/27 20:54:15 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Saves the texture paths from the input line.
 * 
 * @param line The input string.
 * @param m Pointer to the macro structure containing map information.
 * @return 0 if parsing is successful, 1 otherwise.
 */
static int	parse_textures(char *line, t_macro *m)
{
	char	*clean;
	char	*adv_line;
	int		err;

	err = 0;
	clean = ft_strtrim(line, " \t\n");
	if (!clean)
	{
		ft_printf(2, "Error\nMemory allocation failed\n");
		return (1);
	}
	adv_line = clean + 2;
	if (ft_strncmp(clean, "NO ", 3) == 0)
		err = save_texture_path(&(m->map->no), adv_line);
	else if (ft_strncmp(clean, "SO ", 3) == 0)
		err = save_texture_path(&(m->map->so), adv_line);
	else if (ft_strncmp(clean, "WE ", 3) == 0)
		err = save_texture_path(&(m->map->we), adv_line);
	else if (ft_strncmp(clean, "EA ", 3) == 0)
		err = save_texture_path(&(m->map->ea), adv_line);
	free(clean);
	return (err);
}

/**
 * Stores the floor and ceiling color values from the input line if the format is valid.
 * 
 * @param line The input string.
 * @param m Pointer to the macro structure containing map information.
 * @return 0 if parsing is successful, 1 otherwise.
 */
static int	parse_colors(char *line, t_macro *m)
{
	char	*skipped;
	int		err;
	int		*color;

	err = 0;
	color = NULL;
	skipped = get_skipped(line);
	clean_trailing_char(skipped, " \t\n");
	if (!is_valid_fc_format(skipped))
	{
		ft_printf(2, "Error\nFC format is incorrect\n");
		return (1);
	}
	if (ft_skipws(line)[0] == 'F')
		color = m->map->f;
	else if (ft_skipws(line)[0] == 'C')
		color = m->map->c;
	if (color[0] != -1 && color[1] != -1 && color[2] != -1)
	{
		ft_printf(2, "Error\nFC section duplicated\n");
		return (1);
	}
	if (parse_color_values(skipped, color, &err, m))
		return (1);
	return (0);
}

/**
 * Checks if all necessary sections are ready before parsing the map.
 * 
 * @param m Pointer to the macro structure containing map information.
 * @return 1 if all sections are ready, 0 otherwise.
 */
static int	premap_ready(t_macro *m)
{
	int	i;

	i = 0;
	if (m->map->no == NULL || m->map->so == NULL || m->map->we == NULL
		|| m->map->ea == NULL)
		return (0);
	while (i < 3)
	{
		if (m->map->f[i] == -1 || m->map->c[i] == -1)
			return (0);
		i++;
	}
	return (1);
}

/**
 * Add the map line into a linked list.
 * 
 * @param line The input string.
 * @param head Pointer to the head of the linked list.
 * @return 0 if parsing is successful, 1 otherwise.
 */
static int	parse_map(char *line, t_list **head)
{
	t_list	*new;

	clean_trailing_char(line, "\n");
	new = ft_lstnew(ft_strdup(line));
	if (!new)
	{
		ft_printf(2, "Error\nMemory allocation failed\n");
		ft_lstclear(head, free);
		return (1);
	}
	ft_lstadd_back(head, new);
	return (0);
}

/**
 * Parses a line of the input file based on the current section.
 * 
 * @param line The input string.
 * @param m Pointer to the macro structure containing map information.
 * @param section The current section of the input file.
 * @param head Pointer to the head of the linked list.
 * @return 0 if parsing is successful, 1 otherwise.
 */
int	parse_line(char *line, t_macro *m, int section, t_list **head)
{
	int	err;

	err = 0;
	if (section == 0 && *head == NULL)
		return (0);
	else if (section == 1)
		err = parse_textures(line, m);
	else if (section == 2)
		err = parse_colors(line, m);
	else if (section == 0 || section == 3)
	{
		if (!premap_ready(m) && !map_line_is_correct(line))
		{
			ft_printf(2, "Error\nAbnormal section found\n");
			return (1);
		}
		else if (!premap_ready(m) && map_line_is_correct(line))
		{
			ft_printf(2, "Error\n");
			ft_printf(2, "Map starting before other sections are processed\n");
			return (1);
		}
		err = parse_map(line, head);
	}
	return (err);
}
