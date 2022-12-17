#include "../incs/Cub3d.h"

void display_grid(t_mlx *mlx);

int	refresh_screen(t_mlx *mlx)
{
	mlx_clear_window(mlx->ptr, mlx->mlx_win);
	displayMap(mlx);
	display_grid(mlx);
	mlx_square(mlx, mlx->squarex, mlx->squarey, 10, rgb_to_int(0,155,123));
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win,mlx->img , 0, 0);
	return (0);
}

int	main(void)
{
	t_mlx	mlx;
	init_libmlx(&mlx);
	while(42)
	{
		refresh_screen(&mlx);
		mlx_loop(mlx.ptr);
	}
	return(1);
}