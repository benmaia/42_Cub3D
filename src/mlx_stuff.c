#include "../incs/Cub3d.h"

void	img_pix_put(t_mlx *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bits_per_pixel - 8;
    pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bits_per_pixel - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	rgb_to_int(int r, int g, int b)
{
	int	c;

	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	return (c);
}

int	ft_exit(t_mlx *mlx)
{
	(void)mlx;
	exit(0);
	return (0);
}

void init_libmlx(t_mlx *mlx)
{
	mlx->win_x = WIDTH;
	mlx->win_y = HEIGHT;
	mlx->squarex =	WIDTH / 2;
	mlx->squarey = HEIGHT / 2;
	mlx->ptr = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->ptr, mlx->win_x,
			mlx->win_y, "Cub3D");
	mlx->img = mlx_new_image(mlx->ptr, mlx->win_x, mlx->win_y);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	mlx_mouse_hook(mlx->mlx_win, mouse_hook, mlx);
	//mlx_hook(mlx->mlx_win, ON_MOUSEDOWN, (1L << 2), mouse_hook, mlx);
	mlx_hook(mlx->mlx_win, ON_KEYDOWN, (1L << 0), key_hook,mlx);
	mlx_hook(mlx->mlx_win, 17, (1L << 17), ft_exit, mlx);
	mlx_mouse_hide(mlx->ptr, mlx->mlx_win);
	
}
