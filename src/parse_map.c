/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:04:08 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/09 22:48:57 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

void	parse_map(t_mlx *g)
{
	int i;
	int x;

	i = -1;
	x = 0;
	while(g->m->cub[++i])
		if (g->m->cub[i][0] == ' ' || g->m->cub[i][0] == '1'
				|| g->m->cub[i][0] == 0 || g->m->cub[i][0] == '\t')
			if (x == 0)
				x = i;
	if (x == 0)
		exit(1);
	g->m->map = malloc(sizeof(char *) * (i - x + 1));
	if (!g->m->map)
		exit (1);
	i = 0;
	while (g->m->cub[x])
		g->m->map[i++] = ft_strdup(g->m->cub[x++]);
	g->m->map[i] = NULL;
}
