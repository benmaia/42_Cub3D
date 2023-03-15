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
