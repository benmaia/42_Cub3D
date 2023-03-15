/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_boosters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:15:02 by dmarceli          #+#    #+#             */
/*   Updated: 2023/03/15 16:23:15 by dmarceli         ###   ########.fr       */
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

void	set_line_values(t_drawline *l, t_point *start, t_point *end)
{
	start->x = normalizex(start->x);
	end->x = normalizex(end->x);
	start->y = normalizey(start->y);
	end->y = normalizey(end->y);
	l->dx = abs((int)end->x - (int)start->x);
	l->dy = abs((int)end->y - (int)start->y);
	l->sx = (start->x < end->x) ? 1 : -1;
	l->sy = (start->y < end->y) ? 1 : -1;
	l->err = l->dx - l->dy;
}

void	mlx_line_to(t_mlx *mlx, t_point start, t_point end, int color)
{
	t_drawline	l;

	set_line_values(&l, &start, &end);
	while (1)
	{
		img_pix_put(mlx, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		l.e2 = 2 * l.err;
		if (l.e2 > -l.dy)
		{
			l.err -= l.dy;
			start.x += l.sx;
		}
		if (l.e2 < l.dx)
		{
			l.err += l.dx;
			start.y += l.sy;
		}
	}
}

void	mlx_square(t_mlx *mlx, t_point point, int size, int color)
{
	int	i;
	int	j;

	i = point.x;
	while (i < point.x + size)
	{
		j = point.y;
		while (j < point.y + size)
		{
			img_pix_put(mlx, i, j, color);
			j++;
		}
		i++;
	}
}
