/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:09:04 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/11 21:58:39 by bmiguel-         ###   ########.fr       */
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

void	display_grid(t_mlx *mlx)
{
	int	color;
	int	cell_width;
	int	cell_height;

	int x, y;
	color = rgb_to_int(0, 0, 0);
	cell_width = (WIDTH * 0.25 / mlx->m->width);
	cell_height = (HEIGHT * 0.25 / mlx->m->height);
	for (y = 0; y < mlx->m->height; y++)
	{
		for (x = 0; x < mlx->m->width; x++)
		{
			mlx_line_to(mlx, x * cell_width, y * cell_height, (x + 1)
					* cell_width, y * cell_height, color);
			mlx_line_to(mlx, x * cell_width, (y + 1) * cell_height, (x + 1)
					* cell_width, (y + 1) * cell_height, color);
			mlx_line_to(mlx, x * cell_width, y * cell_height, x * cell_width, (y
						+ 1) * cell_height, color);
			mlx_line_to(mlx, (x + 1) * cell_width, y * cell_height, (x + 1)
					* cell_width, (y + 1) * cell_height, color);
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

void	draw_map(t_mlx *mlx)
{
	int	square_size;
	int	x;
	int	y;

	square_size = WIDTH * 0.25 / mlx->m->width;
	for (int row = 0; row < mlx->m->height; row++)
	{
		for (int col = 0; col < mlx->m->width; col++)
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
}

void	displayMap(t_mlx *mlx)
{
	int	minimap_pos_x;
	int	minimap_pos_y;

	draw_map(mlx);
	minimap_pos_x = WIDTH * 0.25 * mlx->p->x / WIDTH / 1.45;
	minimap_pos_y = HEIGHT * 0.25 * mlx->p->y / HEIGHT / 1.45;
	mlx_square(mlx, minimap_pos_x, minimap_pos_y, 4, 0x00);
	mlx_line_to(mlx, minimap_pos_x, minimap_pos_y, minimap_pos_x + mlx->p->dx
			* 5, minimap_pos_y + mlx->p->dy * 5, rgb_to_int(255, 123, 11));
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->img, 0, 0);
}
