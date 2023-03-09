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
		mlx_line_to(mlx, i, end, i, HEIGHT, mlx->m->floor_color);
	if (start != 0)
		mlx_line_to(mlx, i, start, i, 0, mlx->m->sky_color);
}

void	put_pixel_img(t_mlx *data, int x, int y, int color)
{
	char	*dst;
    if (color == 0xFF00FF)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int pick_texture(t_point close, float ang)
{
	ang = normalize_ang(ang);
	if (close.hit)
	{
		if (ang > M_PI)
			return 0;
		else
			return 1;
	}
	else
	{
		if (ang >  M_PI / 2 && ang < (3 * M_PI) / 2)
			return 2;
		else
			return 3;
	}
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
		int text = pick_texture(close, r_angle);
		if (close.hit)
            tex_x = (int)close.x * m->textures[text].w / TILES % m->textures[text].w;
        else
            tex_x = (int)close.y * m->textures[text].h / TILES % m->textures[text].h;
		int y = drawStart;
        while (y < drawEnd)
        {
            // Calculate textures[text] coordinate for current pixel (HEIGHT - line_height) / 2;
			int tex_y = ((y - HEIGHT / 2 + lineheigth / 2) * m->textures[text].h) / lineheigth;            
			// Retrieve pixel value from textures[text] image data
            char *tex_ptr = m->textures[text].addr + (tex_y * m->textures[text].line_len + tex_x * (m->textures[text].bpp / 8));
            int color = *(int *)tex_ptr;
		    put_pixel_img(m, i, y, color);
            y++;
        }
		render_floor(m, i,drawEnd, drawStart);
		r_angle += (FOV / WIDTH);
	}
}
