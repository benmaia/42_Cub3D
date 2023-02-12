#include "../incs/Cub3d.h"

void display_grid(t_mlx *mlx);

int	refresh_screen(t_mlx *mlx)
{
	mlx->img = mlx_new_image(mlx->ptr, mlx->win_x, mlx->win_y);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	mlx_clear_window(mlx->ptr, mlx->mlx_win);
	//display_grid(mlx);
	//mlx_square(mlx, mlx->p->x, mlx->p->y, 10, rgb_to_int(0,155,123));
	cast_rays(mlx);
	displayMap(mlx);
	//mlx_line_to(mlx, mlx->p->x, mlx->p->y, mlx->p->x + mlx->p->dx + 2,mlx->p->y+mlx->p->dy + 2,rgb_to_int(0,0,255));
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win,mlx->img , 0, 0);
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
	while(1)
	{
		refresh_screen(&mlx);
		mlx_hook(mlx.mlx_win, ON_KEYDOWN, (1L << 0), key_hook,&mlx);
		mlx_loop(mlx.ptr);
	}
	return(1);
}