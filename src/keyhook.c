/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:40:32 by dmarceli          #+#    #+#             */
/*   Updated: 2023/03/15 16:21:23 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
		ft_exit(mlx);
	else if (keycode == W_KEY || keycode == S_KEY
		|| keycode == DOWN_KEY || keycode == UP_KEY)
		move_up_and_down(keycode, mlx);
	else if (keycode == D_KEY || keycode == A_KEY)
		move_left_and_right(keycode, mlx);
	else if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
		look_left_and_right(keycode, mlx);
	else if (keycode == M_KEY)
		change_map_status(mlx);
	refresh_screen(mlx);
	return (0);
}

int	mouse_hook(int x, int y, t_mlx *mlx)
{
	float	rot_amt;

	(void)y;
	if (x - WIDTH / 2 > (WIDTH / 50) || x - WIDTH / 2 < -(WIDTH / 50))
	{
		rot_amt = 0.0225;
		if (x - WIDTH / 2 < 0)
			rot_amt = -rot_amt;
		mlx->p->ang = normalize_ang(rot_amt * 1.1 + mlx->p->ang);
		mlx->p->dx = cos(mlx->p->ang) * 5;
		mlx->p->dy = sin(mlx->p->ang) * 5;
		mlx_mouse_move(mlx->ptr, mlx->mlx_win, WIDTH / 2, HEIGHT / 2);
		refresh_screen(mlx);
		return (0);
	}
	return (0);
}

void	put_pixel_img(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (color == 0xFF00FF)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
