/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:35 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/04 12:22:03 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static int parse_textures(char *line, t_macro *macro)
{
	int err = 0;
	char *skipped = ft_skipws(line);
	char *path = ft_skipws(skipped + 2);
	path = clean_trailingws(path);

	if (ft_strncmp(skipped, "NO ", 3) == 0)
		err = save_texture_path(&(macro->map->no), path);
	else if (ft_strncmp(skipped, "SO ", 3) == 0)
		err = save_texture_path(&(macro->map->so), path);
	else if (ft_strncmp(skipped, "WE ", 3) == 0)
		err = save_texture_path(&(macro->map->we), path);
	else if (ft_strncmp(skipped, "EA ", 3) == 0)
		err = save_texture_path(&(macro->map->ea), path);
	return err;
}

static int parse_colors(char *line, t_macro *macro)
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

static int parse_map(char *line, t_list **head)
{
	t_list *new;

	new = ft_lstnew(ft_strdup(line));
	if (!new)
		return (1);
	ft_lstadd_back(head, new);
	return (0);
}

int parse_line(char *line, t_macro *macro, int section, t_list **head)
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