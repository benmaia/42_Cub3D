#include "../incs/Cub3d.h"

void	img_pix_put(t_mlx *img, int x, int y, int color);
void	render_background(t_mlx *mlx, int color);
int		print_pixel(t_mlx *mlx);
int 	draw_square(t_mlx *mlx, int z, int k);


int	main(void)
{
	t_mlx	mlx;

	init_libmlx(&mlx);
	render_background(&mlx, rgb_to_int(255,255,255));
	print_pixel(&mlx);
	mlx_loop(mlx.ptr);
	return(1);
}