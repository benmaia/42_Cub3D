#include "../incs/Cub3d.h"

void	put_pixel_img(t_mlx *data, int x, int y, int color);

void render_gun(t_mlx *mlx)
{
    int x = 0;
    int y = 0;
    char *img_data = mlx->guntexture.addr;
    unsigned int color;

    while (y < mlx->guntexture.h)
    {
        x = 0;
        while (x < mlx->guntexture.w)
        {
            color = *(unsigned int*)(img_data + (y * mlx->guntexture.line_len) + (x * mlx->guntexture.bpp / 8));
            put_pixel_img(mlx, 816 - mlx->guntexture.w + x, 816 - mlx->guntexture.h + y, color);
            x++;
        }
        y++;
    }
}