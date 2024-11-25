/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:35 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/26 00:04:55 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static int	parse_colors(char *line, t_macro *m)
{
	char	*skipped;
	int		err;
	int		*color;

	err = 0;
	color = NULL;
	skipped = ft_skipws(line);
	skipped = ft_skipws(skipped + 1);
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
