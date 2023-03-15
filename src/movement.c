/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:40:32 by dmarceli          #+#    #+#             */
/*   Updated: 2023/03/15 15:42:57 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

int	has_wall(double x, double y, t_mlx *mlx)
{
	int		mapgridx;
	int		mapgridy;

	if ((int)x < 0 || (int)y < 0)
		return (1);
	mapgridx = floor(x / TILES);
	mapgridy = floor(y / TILES);
	if (mapgridx >= mlx->m->width || mapgridy >= mlx->m->height)
		return (2);
	else if (mlx->m->map[mapgridy][mapgridx] == '1')
		return (1);
	return (0);
}

void	move_up_and_down(int keycode, t_mlx *mlx)
{
	double	npx;
	double	npy;

	if (keycode == W_KEY || keycode == UP_KEY)
	{
		npx = mlx->p->x + mlx->p->dx * 0.5;
		npy = mlx->p->y + mlx->p->dy * 0.5;
		if (!has_wall(npx, npy, mlx))
		{
			mlx->p->x += mlx->p->dx * 0.5;
			mlx->p->y += mlx->p->dy * 0.5;
		}
	}
	else if (keycode == S_KEY || keycode == DOWN_KEY)
	{
		npx = mlx->p->x - mlx->p->dx * 0.5;
		npy = mlx->p->y - mlx->p->dy * 0.5;
		if (!has_wall(npx, npy, mlx))
		{
			mlx->p->x -= mlx->p->dx * 0.5;
			mlx->p->y -= mlx->p->dy * 0.5;
		}
	}
}

void	move_left_and_right(int keycode, t_mlx *mlx)
{
	double	angle;
	double	npx;
	double	npy;

	if (keycode == D_KEY)
	{
		angle = mlx->p->ang + M_PI_2;
		npx = mlx->p->x + cos(angle) * 2;
		npy = mlx->p->y + sin(angle) * 2;
		if (!has_wall(npx, npy, mlx))
		{
			mlx->p->x += cos(angle) * 2;
			mlx->p->y += sin(angle) * 2;
		}
	}
	else if (keycode == A_KEY)
	{
		angle = mlx->p->ang - M_PI_2;
		npx = mlx->p->x + cos(angle) * 2;
		npy = mlx->p->y + sin(angle) * 2;
		if (!has_wall(npx, npy, mlx))
		{
			mlx->p->x += cos(angle) * 2;
			mlx->p->y += sin(angle) * 2;
		}
	}
}


void look_left_and_right(int keycode, t_mlx *mlx)
{
	if (keycode == LEFT_KEY)
	{	
		mlx->p->ang -= 0.05;
		if (mlx->p->ang <= 0)
			mlx->p->ang += 2 * M_PI;
		mlx->p->dx = cos(mlx->p->ang) * 5;
		mlx->p->dy = sin(mlx->p->ang) * 5;
	}
	else if (keycode == RIGHT_KEY)
	{
		mlx->p->ang += 0.05;
		if (mlx->p->ang > 2 * M_PI)
			mlx->p->ang -= 2 * M_PI + 0.01;
		mlx->p->dx = cos(mlx->p->ang) * 5;
		mlx->p->dy = sin(mlx->p->ang) * 5;
	}
}

void change_map_status(t_mlx *mlx)
{
	if (mlx->map_enabled)
		mlx->map_enabled = 0;
	else
		mlx->map_enabled = 1;
}

int	key_hook(int keycode,t_mlx *mlx)
{
	if (keycode == 65307)
		ft_exit(mlx);
	else if (keycode == W_KEY || keycode == S_KEY || keycode == DOWN_KEY || keycode == UP_KEY )
		move_up_and_down(keycode, mlx);
	else if (keycode == D_KEY || keycode == A_KEY )
		move_left_and_right(keycode, mlx);
	else if ( keycode == LEFT_KEY || keycode == RIGHT_KEY )
		look_left_and_right(keycode,mlx);
	else if (keycode == M_KEY)
		change_map_status(mlx);
	refresh_screen(mlx);
	return (0);
}


