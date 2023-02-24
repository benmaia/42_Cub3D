#include "../incs/Cub3d.h"
#include <math.h>

unsigned int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


int		has_wall(double x, double y, t_mlx *a)
{
	(void)a;
	int map[MAP_WIDTH][MAP_HEIGHT]=
    {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
	int		mapgridx;
	int		mapgridy;
	if ((int)x < 0 || (int)x > WIDTH ||
	(int)y < 0 || (int)y > HEIGHT)
		return (1);
	mapgridx = floor(x/ TILES);
	mapgridy = floor(y / TILES);
	if (mapgridx >= MAP_WIDTH)
		return (2);
	if (map[mapgridy][mapgridx] == 1)
		return (3);
	return (0);
}

int	key_hook(int keycode,t_mlx *mlx)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == W_KEY || keycode == UP_KEY )
	{
		double npx = mlx->p->x + mlx->p->dx;
		double npy = mlx->p->y + mlx->p->dy;
		if (!has_wall(npx + 5, npy, mlx))
		{
			mlx->p->x += mlx->p->dx * 0.5;
			mlx->p->y += mlx->p->dy * 0.5;
		}
	}
	if (keycode == A_KEY || keycode == LEFT_KEY)
	{
		
		mlx->p->ang -= 0.05;
		if (mlx->p->ang <= 0)
			mlx->p->ang += 2 * M_PI;
		mlx->p->dx = cos(mlx->p->ang) * 5;
		mlx->p->dy = sin(mlx->p->ang) * 5;
	}
	if (keycode == D_KEY || keycode == RIGHT_KEY)
	{
		mlx->p->ang += 0.05;
		if (mlx->p->ang > 2 * M_PI)
			mlx->p->ang -= 2 * M_PI + 0.01;
		mlx->p->dx = cos(mlx->p->ang) * 5;
		mlx->p->dy = sin(mlx->p->ang) * 5;
	}
	if (keycode == S_KEY || keycode == DOWN_KEY)	
	{
		double npx = mlx->p->x - mlx->p->dx;
		double npy = mlx->p->y - mlx->p->dy;
		if (!has_wall(npx, npy + 5, mlx))
		{
			mlx->p->x -= mlx->p->dx;
			mlx->p->y -= mlx->p->dy;
		}
	}
	refresh_screen(mlx);
	return (0);
}

int mouse_hook(int x, int y, t_mlx *mlx)
{
	(void)y;

	double		rot_amt;

	if (x - WIDTH / 2 > ((int)WIDTH / 50) || x - WIDTH / 2 < -((int)WIDTH / 50))
	{
		rot_amt = 1 * MOUSE_SENSI * 0.015;
		if (x - WIDTH / 2 < 0)
			rot_amt = -rot_amt;
		mlx->p->ang += (rot_amt * MOUSE_SENSI);
		mlx->p->dx = cos(mlx->p->ang) * 5;
		mlx->p->dy = sin(mlx->p->ang) * 5;
		refresh_screen(mlx);
		mlx_mouse_move(mlx->ptr, mlx->mlx_win ,WIDTH / 2, HEIGHT / 2);
		return(0);
	}
	return(0);
}