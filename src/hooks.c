/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:43 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/19 12:28:54 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	quit_hook(void *param)
{
	t_macro	*m;

	if (!param)
		return ;
	m = (t_macro *)param;
	if (!m->mlx_cub || !m->mlx_cub)
		return ;
	if (mlx_is_key_down(m->mlx_cub, MLX_KEY_ESCAPE))
		free_and_exit(m);
}

void	release_all(mlx_key_data_t keydata, t_macro *m)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		m->key_w = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		m->key_a = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		m->key_s = 0;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		m->key_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		m->key_left = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		m->key_right = 0;
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_macro	*m;

	m = (t_macro *)param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		mlx_close_window(m->mlx_cub);
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		m->key_w = 1;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		m->key_a = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		m->key_s = 1;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		m->key_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		m->key_left = 1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		m->key_right = 1;
	release_all(keydata, m);
}
