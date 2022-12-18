#include "../incs/Cub3d.h"

int	key_hook(int keycode,t_mlx *mlx)
{
	if (keycode == 65307)
		exit(0);
	printf("Ola\n");
	if (keycode == W_KEY)
	{
		mlx->p->x += mlx->p->dx;
		mlx->p->y += mlx->p->dy; 
		// printf("W\n");
		// if (mlx->p->y> 0)
		// 	mlx->p->y -= 4;
	}
	if (keycode == A_KEY)
	{
		mlx->p->ang -= 0.5;
		if (mlx->p->ang < 0)
		{
			mlx->p->ang += 2 * PI;
		}
		mlx->p->dx = cos(mlx->p->ang) * 5;
		mlx->p->dy = sin(mlx->p->ang) * 5;
		// if (mlx->p->x > 0)
		// 	mlx->p->x -= 4;
		// printf("A\n");
	}
	if (keycode == D_KEY)
	{
		mlx->p->ang += 0.5;
		if (mlx->p->ang > 2*PI)
		{
			mlx->p->ang -= 2 * PI;
		}
		mlx->p->dx = cos(mlx->p->ang) * 5;
		mlx->p->dy = sin(mlx->p->ang) * 5;
		// if (mlx->p->y < WIDTH - 14)
		// 	mlx->p->x += 4;
		// printf("D\n");
	}
	if (keycode == S_KEY)
	{
		mlx->p->x -= mlx->p->dx;
		mlx->p->y -= mlx->p->dy; 
		// printf("S\n");
		// if (mlx->p->y < HEIGHT - 14)
		// 	mlx->p->y += 4;
	}
	printf("%d,\n",mlx->p->x);
	printf("%d,\n",mlx->p->y);
	refresh_screen(mlx);
	return (0);
}

int mouse_hook(int button, int x, int y, t_mlx *mlx)
{

	if (button & 1)
	{
		img_pix_put(mlx, x,y, rgb_to_int(255,255,255));
		mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->img, 0, 0);
	}
	return(0);
}