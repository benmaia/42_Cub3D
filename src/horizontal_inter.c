#include "../incs/Cub3d.h"

void set_initial_ray_values(t_ray *ray, float ang, t_mlx *m)
{
	ray->xwall = 0;
	ray->ywall = 0;
	ray->r_ang = normalize_ang(ang);
	ray->r_dir = upordown(ray->r_ang);
	ray->r_lor = leftorright(ray->r_ang);
	ray->yinter = floor(m->p->y / TILES) * TILES;
	if (ray->r_dir == DOWN)
		ray->yinter += TILES;
	ray->xinter = m->p->x + (ray->yinter - m->p->y)/tan(ray->r_ang);
	ray->ystep = TILES;
	if (ray->r_dir == UP)
		ray->ystep *= -1;
	ray->xstep = TILES / tan(ray->r_ang);
	if ((ray->r_lor == LEFT && ray->xstep > 0) || (ray->r_lor == RIGHT && ray->xstep < 0))
		ray->xstep *= -1;
	ray->nextx = ray->xinter; 
	ray->nexty = ray->yinter;
}

t_point horizontalinter(t_mlx *m, float ang)
{
	t_point inter;
	t_ray	ray;
	set_initial_ray_values(&ray, ang, m);
	while (ray.nextx >= 0 && ray.nexty >= 0)
	{
		if (has_wall(ray.nextx, ray.nexty - (ray.r_dir == UP ? 1 : 0) , m))
		{
			ray.xwall = ray.nextx;
			ray.ywall = ray.nexty;
			break;
		}
		else
		{
			ray.nextx += ray.xstep;
			ray.nexty += ray.ystep; 
		}
	}
	inter.x = ray.xwall;
	inter.y = ray.ywall;
	inter.hit = 1;
	inter.dist2pl = distancebetween(m->p->x, m->p->y, ray.xwall, ray.ywall);
	return(inter);
}
