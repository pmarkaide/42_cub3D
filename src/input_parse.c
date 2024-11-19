/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:35 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 13:00:37 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	parse_textures(char *line, t_macro *m)
{
	int		err;
	char	*skipped;
	char	*path;

	err = 0;
	skipped = ft_skipws(line);
	path = ft_skipws(skipped + 2);
	clean_trailing_char(path, " \t\n");
	if (ft_strncmp(skipped, "NO ", 3) == 0)
		err = save_texture_path(&(m->map->no), path);
	else if (ft_strncmp(skipped, "SO ", 3) == 0)
		err = save_texture_path(&(m->map->so), path);
	else if (ft_strncmp(skipped, "WE ", 3) == 0)
		err = save_texture_path(&(m->map->we), path);
	else if (ft_strncmp(skipped, "EA ", 3) == 0)
		err = save_texture_path(&(m->map->ea), path);
	return (err);
}

static int	parse_colors(char *line, t_macro *m)
{
	char	*skipped;
	int		i;

	i = -1;
	skipped = ft_skipws(line);
	skipped = ft_skipws(skipped + 1);
	while (++i < 3)
	{
		if (ft_skipws(line)[0] == 'F')
			m->map->f[i] = ft_atoi(skipped);
		else if (ft_skipws(line)[0] == 'C')
			m->map->c[i] = ft_atoi(skipped);
		skipped = ft_strchr(skipped, ',');
		if (skipped)
			skipped++;
	}
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
		return (1);
	ft_lstadd_back(head, new);
	return (0);
}

int	parse_line(char *line, t_macro *m, int section, t_list **head)
{
	int	err;

	err = 0;
	if (section == 0)
		return (0);
	if (section == 1)
		err = parse_textures(line, m);
	if (section == 2)
		err = parse_colors(line, m);
	if (section == 3)
	{
		if (!premap_ready(m))
		{
			ft_printf(2,
				"Error\nExpected sections of the file are incorrect\n");
			return (1);
		}
		err = parse_map(line, head);
	}
	return (err);
}
