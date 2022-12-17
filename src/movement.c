#include "../incs/Cub3d.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	(void)mlx;
	if (keycode == 65307)
		exit(0);
	if (keycode == W_KEY)
	{
		printf("W\n");
		if (mlx->squarey > 0)
			mlx->squarey -= 4;
	}
	if (keycode == A_KEY)
	{
		if (mlx->squarex > 0)
			mlx->squarex -= 4;
		printf("A\n");
	}
	if (keycode == S_KEY)
	{
		printf("S\n");
		if (mlx->squarey < HEIGHT - 14)
			mlx->squarey += 4;
	}
	if (keycode == D_KEY)
	{
		if (mlx->squarex < WIDTH - 14)
			mlx->squarex += 4;
		printf("D\n");
	}
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