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

void	mlx_line_to(t_mlx *mlx, t_point start, t_point end, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	start.x = normalizex(start.x);
	end.x = normalizex(end.x);
	start.y = normalizey(start.y);
	end.y = normalizey(end.y);
	dx = abs((int)end.x - (int)start.x);
	dy = abs((int)end.y - (int)start.y);
	sx = (start.x < end.x) ? 1 : -1;
	sy = (start.y < end.y) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		img_pix_put(mlx, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start.y += sy;
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
