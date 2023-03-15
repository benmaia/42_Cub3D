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
	t_point starting;
	t_point ending;
	if (end != HEIGHT)
	{
		starting.x = i;
		starting.y = end;
		ending.x = i;
		ending.y = HEIGHT;
		mlx_line_to(mlx, starting, ending, mlx->m->floor_color);
	}
	if (start != 0)
	{
		starting.x = i;
		starting.y = start;
		ending.x = i;
		ending.y = 0;
		mlx_line_to(mlx, starting, ending, mlx->m->sky_color);
	}
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

void set_raycasting_values(t_line *l, t_mlx *m)
{
	l->close = calc_rays(m, l->r_angle);
	l->pjc = cos(normalize_ang(l->r_angle - m->p->ang)) * l->close.dist2pl * 2;
	l->lineheigth = (m->win_x / l->pjc) * 60; 
	l->drawStart = -l->lineheigth / 2 + m->win_x / 2;
	if(l->drawStart< 0)
		l->drawStart = 0;
	l->drawEnd = l->lineheigth / 2 + m->win_x / 2;
	if(l->drawEnd >= m->win_x)
		l->drawEnd = m->win_x - 1;
	l->text = pick_texture(l->close, l->r_angle);
	if (l->close.hit)
		l->tex_x = (int)l->close.x * m->textures[l->text].w / 34 % m->textures[l->text].w;
	else
		l->tex_x = (int)l->close.y * m->textures[l->text].h / 34 % m->textures[l->text].h;
}

void draw3dline(t_line l, t_mlx *m, int i)
{
	int y;
	int tex_y;
	char *tex_ptr;
	int color;
	y = l.drawStart;
	while (y < l.drawEnd)
	{
		tex_y = ((y - m->win_x / 2 + l.lineheigth / 2) * m->textures[l.text].h) / l.lineheigth;            
		tex_ptr = m->textures[l.text].addr + (tex_y * m->textures[l.text].line_len + l.tex_x * (m->textures[l.text].bpp / 8));
		color = *(int *)tex_ptr;
		put_pixel_img(m, i, y, color);
		y++;
	}
}

void cast_rays(t_mlx *m)
{
	t_line	l;
	int i;
	i = -1;
	l.r_angle = m->p->ang - (FOV / 2);
	while(++i < m->win_x)
	{
		set_raycasting_values(&l, m);
		draw3dline(l, m, i);
		render_floor(m, i,l.drawEnd, l.drawStart);
		l.r_angle += (FOV / m->win_x);
	}
}
