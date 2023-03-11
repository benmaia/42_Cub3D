/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:51:29 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/11 21:59:31 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

char	**map_matrix(t_mlx *g)
{
	int	i;

	g->m->minimap = malloc(sizeof(char *) * (g->m->height + 1));
	g->m->minimap[g->m->height] = NULL;
	i = -1;
	while (g->m->minimap[++i])
	{
		g->m->minimap[i] = ft_calloc(g->m->width, 1);
		ft_memset(g->m->minimap[i], ' ', g->m->width - 1);
		ft_strcpy(g->m->minimap[i], g->m->map[i]);
		g->m->minimap[i][g->m->width - 1] = '\0';
	}
	return (g->m->minimap);
}

void	first_line(char *map, t_mlx *g)
{
	int	j;

	j = -1;
	while (map[++j])
		if (map[j] != '1' && map[j] != ' ')
			wrong_map(g);
}

void	last_line(char *map, t_mlx *g)
{
	int	j;

	j = -1;
	while (map[++j])
		if (map[j] != '1' && map[j] != ' ')
			wrong_map(g);
}

void	mid_lines(char **map, t_mlx *g, int i)
{
	int	j;

	j = -1;
	if (map[i][0] != ' ' && map[i][ft_strlen(map[i]) - 1] != ' '
		&& map[i][0] != '1' && map[i][ft_strlen(map[i]) - 1] != '1')
		wrong_map(g);
	while (map[i][++j])
	{
		if ((map[i][j] == '0' && map[i + 1][j] != '\0' && map[i + 1][j] == ' ')
			|| (map[i][j] == '0' && map[i - 1][j] != '\0' && map[i
				- 1][j] == ' ') || (map[i][j] == '0' && map[i][j + 1] != '\0'
				&& map[i][j + 1] == ' ') || (map[i][j] == '0' && map[i][j
				- 1] != '\0' && map[i][j - 1] == ' '))
			wrong_map(g);
	}
}

void	map_close(t_mlx *g)
{
	int	i;

	i = -1;
	map_matrix(g);
	while (g->m->minimap[++i])
	{
		if (i == 0)
			first_line(g->m->minimap[i], g);
		else if (!g->m->map[i + 1])
			last_line(g->m->minimap[i], g);
		else
			mid_lines(g->m->minimap, g, i);
	}
}
