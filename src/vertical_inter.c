
#include "../incs/Cub3d.h"


void set_initial_ray_values_ver(t_ray *ray, float ang, t_mlx *m)
{
	ray->xwall = 0;
	ray->ywall = 0;
	ray->r_ang = normalize_ang(ang);
	ray->r_dir = upordown(ray->r_ang);
	ray->r_lor = leftorright(ray->r_ang);
	ray->xinter = floor(m->p->x / TILES) * TILES;
	if (ray->r_lor == RIGHT)
		ray->xinter += TILES;
	ray->yinter = m->p->y + (ray->xinter - m->p->x) * tan(ray->r_ang);
	ray->xstep = TILES;
	if (ray->r_lor == LEFT)
		ray->xstep *= -1;
	ray->ystep = TILES * tan(ray->r_ang);
	if ((ray->r_dir == UP && ray->ystep > 0) || (ray->r_dir == DOWN && ray->ystep < 0))
		ray->ystep *= -1;
	ray->nextx = ray->xinter; 
	ray->nexty = ray->yinter;
}


t_point verticalinter(t_mlx *m, float ang)
{
	t_point inter;
	t_ray	ray;
	set_initial_ray_values_ver(&ray, ang, m);
	while (ray.nextx >= 0 && ray.nexty >= 0 )
	{
		if (has_wall(ray.nextx - (ray.r_lor == LEFT ? 1 : 0) , ray.nexty, m))
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
	inter.hit = 0;
	inter.dist2pl = distancebetween(m->p->x, m->p->y, ray.xwall, ray.ywall);
	return(inter);

}
