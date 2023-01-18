#include "../incs/Cub3d.h"

#define DOWN 0
#define UP 1
#define LEFT 2
#define RIGHT 3
#define RAY_NUM 140

float normalize_ang(float angle)
{
	if (angle >= (2 * M_PI))
		angle -= (2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

int upordown(float ang)
{
	if (ang >= 0 && ang <= M_PI) 
		return(DOWN);
	else
		return UP;
}

int leftorright(float ang)
{
	if (ang >= M_PI_2 && ang <= (3 * M_PI_2))
		return(LEFT);
	else
		return(RIGHT);
}

double distancebetween(double x1, double y1, double x2, double y2)
{
	return(sqrt((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1)));
}

t_point horizontalinter(t_mlx *m, float ang)
{
	t_point inter;
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
	while (nextx >= 0 && nextx <= WIDTH && nexty >= 0 && nexty <= HEIGHT)
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
			nextx += xstep;
			nexty += ystep; 
		}
	}
	inter.x = xwall;
	inter.y = ywall;
	if (hit)
	{
		inter.dist2pl = distancebetween(m->p->x, m->p->y, xwall, ywall);
		return(inter);
	}
	inter.dist2pl = INT_MAX;
	return(inter);
}

t_point verticalinter(t_mlx *m, float ang)
{
	t_point inter;
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
	while (nextx >= 0 && nextx <= WIDTH && nexty >= 0 && nexty <= HEIGHT)
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
		inter.dist2pl = distancebetween(m->p->x, m->p->y, xwall, ywall);
		return(inter);
	}
	inter.dist2pl = INT_MAX;
	return(inter);
}

void calc_rays(t_mlx *m, float ang)
{
	ang = normalize_ang(ang);
	t_point h_hit = horizontalinter(m, ang);
	t_point v_hit = verticalinter(m, ang);
	t_point closest = v_hit.dist2pl > h_hit.dist2pl ? h_hit : v_hit;
	mlx_line_to(m, m->p->x, m->p->y, closest.x, closest.y, rgb_to_int(255,0,0));
}

void cast_rays(t_mlx *m)
{
	float r_angle = m->p->ang - (FOV / 2);
	for(int i = 0; i < RAY_NUM; i++)
	{
		calc_rays(m, r_angle);
		r_angle += (FOV / RAY_NUM);
		printf("ang%d:%f\n",i, r_angle);
	}
}