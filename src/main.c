#include "../incs/Cub3d.h"

void display_grid(t_mlx *mlx);

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

t_player *init_player(t_player *player, t_map *map)
{
	player = malloc(sizeof(t_player));
	printf("%d\n", map->width);
	printf("%d\n", map->height);
	player->x = 100;
	player->y = 200;
	player->ang = 0;
	player->dx = cos(player->ang) * 5;
	player->dy = sin(player->ang) * 5;
	return(player);
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
