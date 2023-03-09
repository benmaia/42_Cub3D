#include "../incs/Cub3d.h"
#define ROWS 24
#define COLS 24
void	img_pix_put(t_mlx *img, int x, int y, int color);
int 	draw_square(t_mlx *mlx, int z, int k, int size);

int normalizex(int x)
{
	if (x < 0)
		x = 0;
	if (x > WIDTH)
		x = WIDTH;
	return (x);
}


int normalizey(int x)
{
	if (x < 0)
		x = 0;
	if (x > HEIGHT)
		x = HEIGHT;
	return(x);
}

void mlx_line_to(t_mlx *mlx,int x1, int y1, int x2, int y2, int color)
{
	x1 = normalizex(x1);
	x2 = normalizex(x2);
	y1 = normalizey(y1);
	y2 = normalizey(y2);
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
    int cell_width = (WIDTH / mlx->m->width) ;
    int cell_height =( HEIGHT / mlx->m->height);

    for (y = 0; y < mlx->m->height; y++)
    {
        for (x = 0; x < mlx->m->width; x++)
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

void draw_map(t_mlx *mlx) 
{
    int square_size = mlx->m->width / (WIDTH * 0.25 /mlx->m->width);
  
  	for (int row = 0; row < mlx->m->height; row++) 
  	{
        for (int col = 0; col < mlx->m->width; col++) {
        int x = col * square_size;
        int y = row * square_size;
        if (mlx->m->cub[row][col] == '1') 
            mlx_square(mlx, x, y, square_size, 0x000000);
        else if (mlx->m->cub[row][col] == '0')
            mlx_square(mlx, x, y, square_size, 0xFFFFFF);
        else if (mlx->m->cub[row][col] == 'N')
            mlx_square(mlx, x, y, square_size, 0xDDFF00);    
        else
            mlx_square(mlx, x, y, square_size, 0x00EFEF);
    }
  }
}


void displayMap(t_mlx *mlx)
{
    draw_map(mlx);
    float minimap_scale = 0.145;
    float map_width = WIDTH * minimap_scale;
    float map_height = HEIGHT * minimap_scale;
    int minimap_pos_x = mlx->p->x * (map_width / WIDTH);
    int minimap_pos_y = mlx->p->y * (map_height / HEIGHT);
    mlx_square(mlx, minimap_pos_x, minimap_pos_y, 4, 0x00);
    mlx_line_to(mlx,  minimap_pos_x, minimap_pos_y,  minimap_pos_x + mlx->p->dx * 5, minimap_pos_y + mlx->p->dy * 5, rgb_to_int(255,123,11));
    mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->img, 0, 0);
}
