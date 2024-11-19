/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:43 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/19 13:21:04 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	quit_hook(void *param)
{
	t_macro	*m;

	if (!param)
		return ;
	m = (t_macro *)param;
	if (!m->mlx_cub || !m->keys)
		return ;
	if (mlx_is_key_down(m->mlx_cub, MLX_KEY_ESCAPE))
		free_and_exit(m);
}

void	release_all(mlx_key_data_t keydata, t_macro *m)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		m->keys->key_w = 0;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		m->keys->key_a = 0;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		m->keys->key_s = 0;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		m->keys->key_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		m->keys->key_left = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		m->keys->key_right = 0;
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_macro	*m;

	m = (t_macro *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(m->mlx_cub);
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		m->keys->key_w = 1;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		m->keys->key_a = 1;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		m->keys->key_s = 1;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		m->keys->key_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		m->keys->key_left = 1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		m->keys->key_right = 1;
	release_all(keydata, m);
}
