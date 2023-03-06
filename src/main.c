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

t_player *init_player(t_player *player)
{
	player = malloc(sizeof(t_player));
	player->x = 100;
	player->y = 100;
	player->ang = 1.5;
	player->dx = cos(player->ang) * 5;
	player->dy = sin(player->ang) * 5;
	return(player);
}

int	main(void)
{
	t_mlx	mlx;
	init_libmlx(&mlx);
	mlx.p = init_player(mlx.p);
	refresh_screen(&mlx);
	mlx_loop(mlx.ptr);
	return(1);
}