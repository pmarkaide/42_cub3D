/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:22:26 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/05 15:24:09 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void	quit_hook(void *param)
{
	t_macro *macro;

	macro = param;
	if (mlx_is_key_down(macro->m_mlx, MLX_KEY_ESCAPE))
		free_and_exit(macro);
}
