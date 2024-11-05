/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:46:43 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/05 16:58:30 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_macro	*macro;

	macro = NULL;
	if (argc != 2)
		return (write(2, "Error\nIncorrect number of arguments\n", 36), 1);
	macro = init_macro(macro);
	if (!macro)
		return (write(2, "Error\nMalloc failed\n", 20), 1);
	read_input(argv[1], macro);
	if (validate_map(macro))
	{
		ft_printf(2, "Map validation failed\n");
		return (1);
	}
	init_game(macro);
	render_minimap(macro);
	mlx_terminate(macro->m_mlx->mlx_cub);
	free_and_exit(macro);
}
