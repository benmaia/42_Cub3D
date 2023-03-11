#include "../incs/Cub3d.h"

t_point horizontalinter(t_mlx *m, float ang)
{
	t_point inter;
	inter.hit = 1;
	double xinter, yinter;
	double xstep, ystep;
	double xwall, ywall;
	xwall = 0;
	ywall = 0;
	int hit = 0;

	float r_angle; 
	r_angle = (ang);
	int r_dir = upordown(r_angle);
	int r_lor = leftorright(r_angle);

	yinter = floor(m->p->y / TILES) * TILES;
	if (r_dir == DOWN)
		yinter += TILES;
	xinter = m->p->x + (yinter - m->p->y)/tan(r_angle);
	ystep = TILES;
	if (r_dir == UP)
		ystep *= -1;
	xstep = TILES / tan(r_angle);
	if ((r_lor == LEFT && xstep > 0) || (r_lor == RIGHT && xstep < 0))
		xstep *= -1;
	double nextx = xinter; 
	double nexty = yinter;
	int dof = 0;
	while (nextx >= 0 && nexty >= 0 && dof < INT_MAX)
	{
		if (has_wall(nextx, nexty - (r_dir == UP ? 1 : 0) , m))
		{
			hit = 1;
			xwall = nextx;
			ywall = nexty;
			break;
		}
		else
		{
			dof++;
			nextx += xstep;
			nexty += ystep; 
		}
	}
	inter.x = xwall;
	inter.y = ywall;
	if (hit)
	{

		inter.hit = 1;
		inter.dist2pl = distancebetween(m->p->x, m->p->y, xwall, ywall);
		return(inter);
	}
	inter.dist2pl = INT_MAX;
	return(inter);
}
