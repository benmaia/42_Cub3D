/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:09:04 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/12 13:13:26 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

void	img_pix_put(t_mlx *img, int x, int y, int color);
int		draw_square(t_mlx *mlx, int z, int k, int size);

int	normalizex(int x)
{
	if (x < 0)
		x = 0;
	if (x > WIDTH)
		x = WIDTH;
	return (x);
}

int	normalizey(int x)
{
	if (x < 0)
		x = 0;
	if (x > HEIGHT)
		x = HEIGHT;
	return (x);
}

void	mlx_line_to(t_mlx *mlx, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	x1 = normalizex(x1);
	x2 = normalizex(x2);
	y1 = normalizey(y1);
	y2 = normalizey(y2);
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		img_pix_put(mlx, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	mlx_square(t_mlx *mlx, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = x;
	while (i < x + size)
	{
		j = y;
		while (j < y + size)
		{
			img_pix_put(mlx, i, j, color);
			j++;
		}
		i++;
	}
}

int	draw_map(t_mlx *mlx)
{
	int	square_size;
	int	x;
	int	y;
	int	col;
	int	row;

	square_size = mlx->m->width * TILES * 0.25 / mlx->m->width;
	row = -1;
	while (mlx->m->minimap[++row])
	{
		col = -1;
		while (mlx->m->minimap[row][++col])
		{
			x = col * square_size;
			y = row * square_size;
			if (mlx->m->minimap[row][col] == '1')
				mlx_square(mlx, x, y, square_size, 0x000000);
			else if (mlx->m->minimap[row][col] == '0')
				mlx_square(mlx, x, y, square_size, 0xFFFFFF);
			else if (mlx->m->minimap[row][col] == 'N')
				mlx_square(mlx, x, y, square_size, 0xDDFF00);
			else
				mlx_square(mlx, x, y, square_size, 0x00EFEF);
		}
	}
	return(square_size);
}

void	displayMap(t_mlx *mlx)
{
	double	minimap_pos_x;
	double	minimap_pos_y;
	int sq = draw_map(mlx);
	float scale = (float)sq / (float)TILES;
	minimap_pos_x = mlx->p->x * scale - sq / 8;
	minimap_pos_y = mlx->p->y * scale - sq / 8;
	mlx_square(mlx, minimap_pos_x , minimap_pos_y, sq / 2 , 0xFF0000);
	mlx_line_to(mlx, minimap_pos_x + sq / 4 , minimap_pos_y + sq / 4, minimap_pos_x + mlx->p->dx
		* 5, minimap_pos_y + mlx->p->dy * 5, rgb_to_int(255, 123, 11));
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->img, 0, 0);
}
