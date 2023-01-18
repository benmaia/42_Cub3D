#	ifndef CUB3D_H
#	define CUB3D_H

#	define 	W_KEY 119
#	define 	A_KEY 97
#	define 	S_KEY 115
#	define 	D_KEY 100
#	define 	ESC 65307
#	define 	ON_MOUSEDOWN 4
#	define	ON_MOUSEUP 5
#	define	ON_KEYDOWN 2

# 	define WIDTH 816
# 	define HEIGHT 816
#	define MAP_HEIGHT 24
#	define MAP_WIDTH 24

#	define SPEED 5
#	define TILES 34

#	define FOV M_PI / 3

#	include <stdio.h>
# 	include <stdlib.h>
#	include <unistd.h>
#	include <limits.h>
#	include <math.h>
#	include "../mlx_linux/mlx.h"

typedef struct s_point{
	double x;
	double y;
	double dist2pl;
}				t_point;

typedef struct s_player{
	double x;
	double y;
	float ang;
	float dx;
	float dy;
	float rx;
	float ry;
}				t_player;

typedef struct	s_mlx {
	void	*ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx_win;
	int 	squarex;
	int 	squarey;
	int		win_x;
	int		win_y;
	int 	**map;
	t_player	*p;
}				t_mlx;

typedef struct s_data
{
	t_mlx		m;
}				t_data;


void 	init_libmlx(t_mlx *mlx);
int		refresh_screen(t_mlx *mlx);
void	img_pix_put(t_mlx *img, int x, int y, int color);
int		rgb_to_int(int r, int g, int b);
int		key_hook(int keycode, t_mlx *mlx);
int 	mouse_hook(int button, int x, int y, t_mlx *mlx);
void	displayMap(t_mlx *mlx);
void 	mlx_square(t_mlx *mlx, int x, int y, int size, int color);
int 	mouse_hook(int button, int x, int y, t_mlx *mlx);
void 	mlx_line_to(t_mlx *mlx,int x1, int y1, int x2, int y2, int color);
void 	cast_rays(t_mlx *m);
int		has_wall(double x, double y, t_mlx *a);

#	endif