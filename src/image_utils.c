/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:22:37 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/12/30 20:05:59 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Combines the RGBA values into a single integer.
 * 
 * @param r The red component.
 * @param g The green component.
 * @param b The blue component.
 * @param a The alpha component.
 * @return The combined RGBA value as an integer.
 */
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * Skips whitespaces and key element of the line.
 * 
 * For "F 255,255,255", returns the starting of the digit
 * 
 * @param line The input string.
 * @return A pointer to the first non-whitespace character after the key.
 */
char	*get_skipped(char *line)
{
	char	*skipped;

	skipped = ft_skipws(line);
	skipped = ft_skipws(skipped + 1);
	return (skipped);
}
