#include "../incs/Cub3d.h"

void	img_pix_put(t_mlx *img, int x, int y, int color);
int draw_square(t_mlx *mlx, int z, int k, int size);

void mlx_line_to(t_mlx *mlx,int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;
    while (1)
    {
        img_pix_put(mlx, x1, y1, color);
        if (x1 == x2 && y1 == y2) 
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}


void display_grid(t_mlx *mlx)
{
    int x, y;
    int color = rgb_to_int(0,0,0);
    int cell_width = WIDTH / 24;
    int cell_height = HEIGHT / 24;

    for (y = 0; y < 24; y++)
    {
        for (x = 0; x < 24; x++)
        {
            mlx_line_to(mlx, x * cell_width, y * cell_height, (x+1) * cell_width, y * cell_height, color);
            mlx_line_to(mlx, x * cell_width, (y+1) * cell_height, (x+1) * cell_width, (y+1) * cell_height, color);
            mlx_line_to(mlx, x * cell_width, y * cell_height, x * cell_width, (y+1) * cell_height, color);
            mlx_line_to(mlx, (x+1) * cell_width, y * cell_height, (x+1) * cell_width, (y+1) * cell_height, color);
        }
    }
}
void mlx_square(t_mlx *mlx, int x, int y, int size, int color)
{
    
    int i;
    int j;
    i = x;
    while (i < x + size)
    {
        j = y;
        while (j < y + size)
        {
            img_pix_put(mlx, i, j, color);
            j++;
        }
        i++;
    }
}

void draw_map(t_mlx *mlx, int map[24][24])
{
  int square_height = (HEIGHT / 24 ) / 4;
  for (int row = 0; row < 24; row++)
  {
    int col;
    for (col = 0; col < 24; col++)
    {
      if (map[row][col] == 1)
        mlx_square(mlx, col * square_height, row * square_height, square_height, 0x000000);
      else if (map[row][col] == 0)
        mlx_square(mlx, col * square_height, row * square_height, square_height, 0xFFFFFF);
    }
  }
}
void displayMap(t_mlx *mlx)
{
    int map[MAP_WIDTH][MAP_HEIGHT]=
    {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    draw_map(mlx,map);
	int pos_playerx;
	int pos_playery;
	pos_playerx = floor((mlx->p->x * 24) / 24) / 4 * 0.92 ;
	pos_playery = floor((mlx->p->y * 24) / 24) / 4 * 0.92 ;
	mlx_square(mlx, pos_playerx , pos_playery , 4, 0x00FF11);
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win,mlx->img , 0, 0);
}

