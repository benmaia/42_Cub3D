#include "../incs/Cub3d.h"

int	print_pixel(t_mlx *mlx);

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

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int mouse_hook(int button, int x, int y, t_mlx *mlx)
{

	if (button & 1)
	{
		my_mlx_pixel_put(mlx, x,y, rgb_to_int(255,255,255));
		mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->img, 0, 0);
	}
	return(0);
}

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
	print_pixel(mlx);
	return (0);
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
	mlx_hook(mlx->mlx_win, ON_MOUSEDOWN, (1L << 2), mouse_hook, mlx);
	mlx_hook(mlx->mlx_win, ON_KEYDOWN, (1L << 0), key_hook, mlx);
	mlx_hook(mlx->mlx_win, 17, (1L << 17), ft_exit, mlx);
}
int draw_square(t_mlx *mlx, int z, int k)
{
	int x, y;
	for (x = 0; x < 10; x++) {
		for (y = 0; y < 10; y++) {
			my_mlx_pixel_put(mlx, z + x, k+ y, rgb_to_int(0,155,123));
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->img, 0, 0);
	return(0);
}

void	render_background(t_mlx *mlx, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			img_pix_put(mlx, j++, i, color);
		}
		++i;
	}
}

int	print_pixel(t_mlx *mlx)
{
	render_background(mlx, rgb_to_int(255,255,255));
	draw_square(mlx, mlx->squarex, mlx->squarey);
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win,mlx->img , 0, 0);
	return (0);
}
