#include "../incs/Cub3d.h"


t_point calc_rays(t_mlx *m, float ang)
{
	ang = normalize_ang(ang);
	t_point h_hit = horizontalinter(m, ang);
	t_point v_hit = verticalinter(m, ang);
	if (v_hit.dist2pl > h_hit.dist2pl)
		return(h_hit);
	else
		return(v_hit);
}

void render_floor(t_mlx *mlx,int i ,int end, int start)
{
	if (end != HEIGHT)
		mlx_line_to(mlx, i, end, i, HEIGHT,rgb_to_int(123,125,123) );
	if (start != 0)
		mlx_line_to(mlx, i, start, i, 0,0x00FFFF);
}

void	put_pixel_img(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void cast_rays(t_mlx *m)
{
	int i;
	i = -1;
	float r_angle = m->p->ang - (FOV / 2);
	while(++i < WIDTH)
	{
		int tex_x;
		t_point close = calc_rays(m, r_angle);
		float pjc = cos(normalize_ang(r_angle - m->p->ang)) * close.dist2pl * 2;
		int lineheigth = (HEIGHT / pjc) * 60; 
    	int drawStart = -lineheigth / 2 + HEIGHT / 2;
      	if(drawStart < 0)
			drawStart = 0;
    	int drawEnd = lineheigth / 2 + HEIGHT / 2;
      	if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		if (close.hit)
            tex_x = (int)close.x * m->texture.w / TILES % m->texture.w;
        else
            tex_x = (int)close.y * m->texture.h / TILES % m->texture.h;
		int y = drawStart;
        while (y < drawEnd)
        {
            // Calculate texture coordinate for current pixel (W_H - vars->p_vec->line_height) / 2;
			int tex_y = ((y - HEIGHT / 2 + lineheigth / 2) * m->texture.h) / lineheigth;            
			// Retrieve pixel value from texture image data
            char *tex_ptr = m->texture.addr + (tex_y * m->texture.line_len + tex_x * (m->texture.bpp / 8));
            int color = *(int *)tex_ptr;
		    put_pixel_img(m, i, y, color);
            y++;
        }
		render_floor(m, i,drawEnd, drawStart);
		r_angle += (FOV / WIDTH);
	}
}