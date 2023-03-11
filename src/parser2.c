/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:43:00 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/11 14:56:45 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"
#include <stdio.h>

void	parse_colors(t_mlx *g)
{
	int	i;

	i = -1;
	while (g->m->cub[++i])
	{
		if (!ft_strncmp(g->m->cub[i], "C ", 2))
			g->m->sky = ft_substr(g->m->cub[i], 2, ft_strlen(g->m->cub[i]));
		if (!ft_strncmp(g->m->cub[i], "F ", 2))
			g->m->floor = ft_substr(g->m->cub[i], 2, ft_strlen(g->m->cub[i]));
	}
	i = -1;
	if (g->m->sky == NULL || g->m->floor == NULL)
		wrong_map(g);
	while (g->m->sky[++i])
		if ((g->m->sky[i] > '9' && g->m->sky[i] != ',') || (g->m->sky[i] < '0'
				&& g->m->sky[i] != ','))
			wrong_map(g);
	i = -1;
	while (g->m->floor[++i])
		if ((g->m->floor[i] > '9' && g->m->floor[i] != ',')
			|| (g->m->floor[i] < '0' && g->m->floor[i] != ','))
			wrong_map(g);
}

void	parse_sky(t_mlx *g)
{
	int		i;
	int		j;
	char	*sky;

	i = -1;
	j = 0;
	g->m->sky_colors = malloc((sizeof(int) * 3));
	g->m->sky_colors[j] = ft_atoi(g->m->sky);
	while (g->m->sky[++i])
	{
		if (g->m->sky[i] == ',')
		{
			if (++j == 3 || !g->m->sky[++i] || g->m->sky[i] == ','
				|| g->m->sky[i] == '\n')
				exit(1);
			sky = ft_substr(g->m->sky, i, ft_strlen(g->m->sky));
			g->m->sky_colors[j] = ft_atoi(sky);
			free(sky);
		}
	}
}

void	parse_floor(t_mlx *g)
{
	int		i;
	int		j;
	char	*floor;

	i = -1;
	j = 0;
	g->m->floor_colors = malloc(sizeof(int) * 3);
	g->m->floor_colors[j] = ft_atoi(g->m->floor);
	while (g->m->floor[++i])
	{
		if (g->m->floor[i] == ',')
		{
			if (++j == 3 || !g->m->floor[++i] || g->m->floor[i] == ','
				|| g->m->floor[i] == '\n')
				wrong_map(g);
			floor = ft_substr(g->m->floor, i, ft_strlen(g->m->floor));
			g->m->floor_colors[j] = ft_atoi(floor);
			free(floor);
		}
	}
}

void	parse_textures(t_mlx *g)
{
	int	i;

	i = -1;
	g->m->texture = malloc(sizeof(char *) * 4);
	while (++i < 4)
		g->m->texture[i] = NULL;
	i = -1;
	while (g->m->cub[++i])
	{
		if (!ft_strncmp(g->m->cub[i], "NO ", 3))
			g->m->texture[0] = ft_substr(g->m->cub[i], 3,
					ft_strlen(g->m->cub[i]));
		if (!ft_strncmp(g->m->cub[i], "SO ", 3))
			g->m->texture[1] = ft_substr(g->m->cub[i], 3,
					ft_strlen(g->m->cub[i]));
		if (!ft_strncmp(g->m->cub[i], "WE ", 3))
			g->m->texture[2] = ft_substr(g->m->cub[i], 3,
					ft_strlen(g->m->cub[i]));
		if (!ft_strncmp(g->m->cub[i], "EA ", 3))
			g->m->texture[3] = ft_substr(g->m->cub[i], 3,
					ft_strlen(g->m->cub[i]));
	}
}

void	parse_values(t_mlx *g)
{
	int	i;

	i = -1;
	parse_textures(g);
	while (++i < 4)
		if (g->m->texture[i] == NULL
			|| !is_texture_path_valid(g->m->texture[i]))
			wrong_map(g);
	parse_colors(g);
	parse_sky(g);
	i = -1;
	while (++i < 3)
		if (g->m->sky_colors[i] < 0 || g->m->sky_colors[i] > 255)
			wrong_map(g);
	g->m->sky_color = rgb_to_int(g->m->sky_colors[0], g->m->sky_colors[1],
			g->m->sky_colors[2]);
	parse_floor(g);
	i = -1;
	while (++i < 3)
		if (g->m->floor_colors[i] < 0 || g->m->floor_colors[i] > 255)
			wrong_map(g);
	g->m->floor_color = rgb_to_int(g->m->floor_colors[0], g->m->floor_colors[1],
			g->m->floor_colors[2]);
}
