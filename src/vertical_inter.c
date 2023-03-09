
#include "../incs/Cub3d.h"

t_point verticalinter(t_mlx *m, float ang)
{
	t_point inter;
	inter.hit = 0;
	double xinter, yinter;
	double xstep, ystep;
	double xwall, ywall;
	int hit = 0;
	xwall = 0;
	ywall = 0;
	float r_angle = normalize_ang(ang);
	int r_dir = upordown(r_angle);
	int r_lor = leftorright(r_angle);

	//FIND X-interseption
	xinter = floor(m->p->x / TILES) * TILES;
	if (r_lor == RIGHT)
		xinter += TILES;
	//FIND Y-interseption
	yinter = m->p->y + (xinter - m->p->x) * tan(r_angle);
	//find STEPS
	//xstep
	xstep = TILES;
	if (r_lor == LEFT)
		xstep *= -1;
	//ystep
	ystep = TILES * tan(r_angle);
	if ((r_dir == UP && ystep > 0) || (r_dir == DOWN && ystep < 0))
		ystep *= -1;
	// next intersection
	double nextx = xinter; 
	double nexty = yinter;
	//make sure that mf hits a wall
	// loop untill it finds a wall or leaves canvas, increments with x and y step
	while (nextx >= 0 && nexty >= 0 )
	{
		if (has_wall(nextx - (r_lor == LEFT ? 1 : 0) , nexty, m))
		{
			hit = 1; 
			xwall = nextx;
			ywall = nexty;
			break;
		}
		else 
		{
			nextx += xstep;
			nexty += ystep;
		}
	}
	inter.x = xwall;
	inter.y = ywall;
	if (hit)
	{
		inter.hit = 0;
		inter.dist2pl = distancebetween(m->p->x, m->p->y, xwall, ywall);
		return(inter);
	}
	inter.dist2pl = INT_MAX;
	return(inter);
}
