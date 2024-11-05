/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:22:26 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/05 16:30:31 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void quit_hook(void *param)
{
    t_macro *macro;

    if (!param)
        return;
    macro = (t_macro *)param;
    if (!macro->m_mlx || !macro->m_mlx->mlx_cub)
        return;
    if (mlx_is_key_down(macro->m_mlx->mlx_cub, MLX_KEY_ESCAPE))
        free_and_exit(macro);
}