/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse_fc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:51:42 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/12/27 20:44:35 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Checks for integer overflow or underflow during conversion.
 * 
 * @param nb The current number.
 * @param next_char The next character to be added to the number.
 * @param neg The sign of the number.
 * @return 1 if overflow or underflow occurs, 0 otherwise.
 */
static int	check_overflow(long nb, char next_char, int neg)
{
	if (neg > 0)
	{
		if (nb > LONG_MAX / 10)
			return (1);
		if (nb == LONG_MAX / 10 && next_char - '0' > LONG_MAX % 10)
			return (1);
	}
	else
	{
		if (nb > -(long)(LONG_MIN / 10))
			return (1);
		if (nb == -(long)(LONG_MIN / 10) && next_char - '0' > -(LONG_MIN % 10))
			return (1);
	}
	return (0);
}

/**
 * Converts a string to an integer, checking for errors.
 * 
 * @param str The input string.
 * @param error Pointer to an integer to store error status.
 * @return The converted integer.
 */
static int	nbr_to_int(char *str, int *error)
{
	long	nb;
	int		neg;

	nb = 0;
	neg = 1;
	while (*str && (ft_isspace(*str)))
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (!*str || !ft_isdigit(*str))
		*error = 1;
	while (*str && ft_isdigit(*str))
	{
		if (check_overflow(nb, *str, neg))
			*error = 1;
		nb = 10 * nb + *str++ - '0';
	}
	if (*str != '\0')
		*error = 1;
	nb *= neg;
	if (nb < INT_MIN || nb > INT_MAX)
		*error = 1;
	return ((int)nb);
}

/**
 * Validates the format of the floor/ceiling color integers.
 * 
 * Only allowed format is: 255,255,255
 * 
 * @param line The input string.
 * @return 1 if the format is valid, 0 otherwise.
 */
int	is_valid_fc_format(char *line)
{
	int	i;

	i = 0;
	if (!ft_isdigit(line[i]))
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != ',')
		return (0);
	i++;
	if (!ft_isdigit(line[i]))
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != ',')
		return (0);
	i++;
	if (!ft_isdigit(line[i]))
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

/**
 * Extracts a number string from the input, up to the next comma.
 * 
 * @param skipped The input string.
 * @param m Pointer to the macro structure.
 * @return A pointer to the extracted number string.
 */
static char	*extract_number_string(char *skipped, t_macro *m)
{
	int		len;
	char	*temp;

	len = ft_strlenc(skipped, ',');
	temp = (char *)malloc((len + 1) * sizeof(char));
	if (!temp)
	{
		ft_printf(2, "Error\nMalloc failed\n");
		free_macro(m);
	}
	ft_strncpy(temp, skipped, len);
	temp[len] = '\0';
	return (temp);
}

/**
 * Stores the color values from the input string.
 * 
 * @param skipped The input string.
 * @param color Array to store the parsed color values.
 * @param err Pointer to an integer to store error status.
 * @param m Pointer to the macro structure.
 * @return 0 if parsing is successful.
 */
int	parse_color_values(char *skipped, int *color, int *err, t_macro *m)
{
	int		count;
	int		i;
	char	*temp;

	count = 0;
	i = 0;
	while (++i < 4)
	{
		temp = extract_number_string(skipped, m);
		color[count] = nbr_to_int(temp, err);
		free(temp);
		if (*err)
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
