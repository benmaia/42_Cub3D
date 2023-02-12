#include "../incs/Cub3d.h"


t_point calc_rays(t_mlx *m, float ang)
{
	ang = normalize_ang(ang);
	t_point h_hit = horizontalinter(m, ang);
	t_point v_hit = verticalinter(m, ang);
	t_point closest = v_hit.dist2pl > h_hit.dist2pl ? h_hit : v_hit;
	return(closest);
}

void cast_rays(t_mlx *m)
{
	int i;
	int color;
	i = -1;
	float r_angle = m->p->ang - (FOV / 2);
	while(++i < WIDTH)
	{
		t_point close = calc_rays(m, r_angle);
		if (close.hit)
			color = 0x80FF0000;
		else 
			color = 0xFF00FF00;
		float pjc = cos(normalize_ang(r_angle - m->p->ang)) * close.dist2pl;
		int lineheigth = (HEIGHT / pjc) * 60; 
    	int drawStart = -lineheigth / 2 + HEIGHT / 2;
      	if(drawStart < 0)
			drawStart = 0;
    	int drawEnd = lineheigth / 2 + HEIGHT / 2;
      	if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		mlx_line_to(m, i,drawStart , i, drawEnd, color);
		r_angle += (FOV / WIDTH);
	}
}