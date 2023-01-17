#include "../incs/Cub3d.h"

#define DOWN 0
#define UP 1
#define LEFT 2
#define RIGHT 3

float normalize_ang(float angle)
{
	if (angle >= (2 * PI))
		angle -= (2 * PI);
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}

int upordown(float ang)
{
	if (ang > 0 && ang < PI)
		return(DOWN);
	else
		return(UP);
}
int leftorright(float ang)
{
	if (ang < 0.5 * PI || ang > 1.5 * PI)
		return(RIGHT);
	else
		return(LEFT);
}

void horizontalinter(t_mlx *m)
{
	double xinter, yinter;
	double xstep, ystep;
	double xwall, ywall;
	float r_angle = normalize_ang(m->p->ang);
	int r_dir = upordown(r_angle);
	int r_lor = leftorright(r_angle);
	yinter = floor(m->p->y / TILES) * TILES;
	if (r_dir)
		yinter += TILES;
	xinter = m->p->x + (yinter - m->p->y)/ - tan(r_angle);
	ystep = TILES;
	if (r_dir)
		ystep *= -1;
	xstep = TILES / tan(r_angle);
	if ((r_lor == LEFT && xstep > 0) || (r_lor == RIGHT && xstep < 0))
		xstep *= -1;
	double nextx = xinter; 
	double nexty = yinter;
	if (r_dir == UP)
		nexty -= 1;
	while (nextx >= 0 && nextx <= WIDTH && nexty >= 0 && nexty <= HEIGHT)
	{
		if (has_wall(nextx, nexty, m))
		{
			xwall = nextx;
			ywall = nexty;
			mlx_line_to(m,m->p->x, m->p->y, xwall,ywall ,rgb_to_int(0,255,0));
			break;
		}
		else {
			nextx += xstep;
			nexty += ystep;
		}
	}
}

void verticalinter(t_mlx *m)
{
	double xinter, yinter;
	double xstep, ystep;
	double xwall, ywall;

	float r_angle = normalize_ang(m->p->ang);
	int r_dir = upordown(r_angle);
	int r_lor = leftorright(r_angle);

	//FIND X-interseption
	xinter = floor(m->p->x / TILES) * TILES;
	if (r_lor == RIGHT)
		xinter += TILES;
	//FIND Y-interseption
	yinter = m->p->y + (xinter - m->p->x) * -tan(r_angle);
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
	if (r_lor == LEFT)
		nextx -= 1;
	// loop untill it finds a wall or leaves canvas, increments with x and y step
	while (nextx >= 0 && nextx <= WIDTH && nexty >= 0 && nexty <= HEIGHT)
	{
		if (has_wall(nextx, nexty, m))
		{
			xwall = nextx;
			ywall = nexty;
			mlx_line_to(m,m->p->x, m->p->y, xwall,ywall ,rgb_to_int(0,255,0));
			break;
		}
		else {
			nextx += xstep;
			nexty += ystep;
		}
	}
}

void cast_rays(t_mlx *m)
{
	horizontalinter(m);
	verticalinter(m);
}