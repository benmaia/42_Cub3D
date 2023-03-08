#include "../incs/Cub3d.h"

int	refresh_screen(t_mlx *mlx)
{
	mlx_clear_window(mlx->ptr, mlx->mlx_win);
	cast_rays(mlx);
	displayMap(mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->img , 0, 0);
	render_gun(mlx);
	mlx_do_sync(mlx->ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_mlx	mlx;
	map_parser(argc, argv, &mlx);
	init_libmlx(&mlx);
	mlx.p = init_player(mlx.p, mlx.m);
	refresh_screen(&mlx);
	mlx_loop(mlx.ptr);
	return(1);
}
