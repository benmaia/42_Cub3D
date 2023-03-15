/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:13:25 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/15 20:24:46 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

int	set_line_ter(int start, int end)
{
	if (start < end)
		return (1);
	return (-1);
}

void	cast_rays(t_mlx *m)
{
	t_line	l;
	int		i;

	i = -1;
	l.r_angle = m->p->ang - (FOV / 2);
	while (++i < m->win_x)
	{
		set_raycasting_values(&l, m);
		draw3dline(l, m, i);
		render_floor(m, i, l.drawEnd, l.drawStart);
		l.r_angle += (FOV / m->win_x);
	}
}
