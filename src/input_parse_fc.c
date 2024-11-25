/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse_fc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:51:42 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/25 22:58:56 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
