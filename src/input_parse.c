/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:35 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/22 13:43:15 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	parse_textures(char *line, t_macro *m)
{
	char	*skipped;
	char	*cleaned_path;
	int		err;

	err = 0;
	skipped = ft_skipws(line);
	cleaned_path = ft_skipws(skipped + 2);
	if (!cleaned_path)
	{
		ft_printf(2, "Error\nMemory allocation failed\n");
		return (1);
	}
	clean_trailing_char(cleaned_path, " \t\n");
	if (ft_strncmp(skipped, "NO ", 3) == 0)
		err = save_texture_path(&(m->map->no), cleaned_path);
	else if (ft_strncmp(skipped, "SO ", 3) == 0)
		err = save_texture_path(&(m->map->so), cleaned_path);
	else if (ft_strncmp(skipped, "WE ", 3) == 0)
		err = save_texture_path(&(m->map->we), cleaned_path);
	else if (ft_strncmp(skipped, "EA ", 3) == 0)
		err = save_texture_path(&(m->map->ea), cleaned_path);
	return (err);
}

int is_valid_CF_format(char *line)
{
    int i = 0;
    if (!ft_isdigit(line[i]))
        return 0;
    while (ft_isdigit(line[i]))
        i++;
    if (line[i] != ',')
        return 0;
    i++;
    if (!ft_isdigit(line[i]))
        return 0;
    while (ft_isdigit(line[i]))
        i++;
    if (line[i] != ',')
        return 0;
    i++;
    if (!ft_isdigit(line[i]))
        return 0;
    while (ft_isdigit(line[i]))
        i++;
    return 1;
}

static int	parse_colors(char *line, t_macro *m)
{
	char	*skipped;
	int		count;
	int		i;
	int		err;
	int 	*color;

	i = 0;
	count = 0;
	err = 0;
	skipped = ft_skipws(line);
	skipped = ft_skipws(skipped + 1);
	clean_trailing_char(skipped, " \t\n");
	if(!is_valid_CF_format(skipped))
		return(1);
	if (ft_skipws(line)[0] == 'F')
		color = m->map->f;
	else if (ft_skipws(line)[0] == 'C')
		color = m->map->c;
	while (++i < 3)
	{
		int len = ft_strlenc(skipped, ',');
		char *temp = (char *)malloc((len + 1) * sizeof(char));
		if (!temp)
		{
			ft_printf(2, "Error\nMalloc failed\n");
			free_macro(m);
		}
		ft_strncpy(temp, skipped, len);
		temp[len] = '\0';
		color[count] = nbr_to_int(temp, &err);
		free(temp);
		{
			ft_printf(2, "Error\nInteger overflow or underflow\n");
			free_macro(m);
		}
		skipped = ft_strchr(skipped, ',');
		if (skipped)
			skipped++;
		count++;
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
	if (section == 0)
		return (0);
	if (section == 1)
		err = parse_textures(line, m);
	if (section == 2)
		err = parse_colors(line, m);
	if (section == 3)
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
