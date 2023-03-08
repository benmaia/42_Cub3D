#	ifndef CUB3D_H
#	define CUB3D_H

#	define 	W_KEY 119
#	define 	A_KEY 97
#	define 	S_KEY 115
#	define 	D_KEY 100
#	define 	UP_KEY 65362
#	define 	RIGHT_KEY 65363
#	define 	LEFT_KEY 65361
#	define 	DOWN_KEY 65364
#	define 	ESC 65307
#	define 	ON_MOUSEDOWN 4
#	define	ON_MOUSEUP 5
#	define	ON_KEYDOWN 2
# 	define MOUSE_SENSI 1.5
#	define DOWN 0
#	define UP 1
#	define LEFT 2
#	define RIGHT 3

# 	define WIDTH 920
# 	define HEIGHT 920

#	define SPEED 5
#	define TILES 34

#	define FOV M_PI / 3

#	include <math.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <unistd.h>
#	include <limits.h>
#	include <fcntl.h>
#	include <stdbool.h> 
#	include "../mlx_linux/mlx.h"

typedef struct s_map{
	char orientation;
	int fd;
	char	**map;
	int	height;
	int	width;
	int p_x;
	int p_y;
	int players;
} t_map;

typedef struct s_point{
	double x;
	double y;
	double dist2pl;
	int hit;
}				t_point;

typedef struct	s_line
{
	t_point		start;
	t_point		end;
	int			color;
}				t_line;

typedef struct s_player{
	double x;
	double y;
	float ang;
	float dx;
	float dy;
	float rx;
	float ry;
}				t_player;

typedef struct s_image
{
	void		*img_ptr;
	char		*addr;
	int			h;
	int			w;
	int			bpp;
	int			endian;
	int			line_len;
}		t_image;

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
	t_image		texture;
	t_image		guntexture;
	t_player	*p;
	t_map	*m;
}				t_mlx;

typedef struct s_data
{
	t_mlx		m;
}				t_data;


void 	init_libmlx(t_mlx *mlx);
t_player *init_player(t_player *player, t_map *map);
int		refresh_screen(t_mlx *mlx);
void	img_pix_put(t_mlx *img, int x, int y, int color);
int		rgb_to_int(int r, int g, int b);
int		key_hook(int keycode, t_mlx *mlx);
void	displayMap(t_mlx *mlx);
void 	mlx_square(t_mlx *mlx, int x, int y, int size, int color);
int 	mouse_hook(int x, int y, t_mlx *mlx);
void 	mlx_line_to(t_mlx *mlx,int x1, int y1, int x2, int y2, int color);
void 	cast_rays(t_mlx *m);
int		has_wall(double x, double y, t_mlx *a);
float	normalize_ang(float angle);
int		upordown(float ang);
int		leftorright(float ang);
double	distancebetween(double x1, double y1, double x2, double y2);
int		range(int val, int min, int max);
t_point horizontalinter(t_mlx *m, float ang);
t_point verticalinter(t_mlx *m, float ang);
void render_gun(t_mlx *mlx);
int	ft_exit(t_mlx *mlx);

/*############## UTILS ###############*/


unsigned	int ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);

/*/############ PARSER #############*/
void	map_parser(int argc, char **argv, t_mlx *g);

#	endif
