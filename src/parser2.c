/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:43:00 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/09 00:00:28 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

void	parse_colors(t_mlx *g)
{
	int	i;

	i = -1;
	g->m->sky = NULL;
	g->m->floor = NULL;
	while(g->m->cub[++i])
	{
		if (!ft_strncmp(g->m->cub[i], "C ", 2))
			g->m->sky = ft_substr(g->m->cub[i], 2, ft_strlen(g->m->cub[i]));
		if (!ft_strncmp(g->m->cub[i], "F ", 2))
			g->m->floor = ft_substr(g->m->cub[i], 2, ft_strlen(g->m->cub[i]));
	}
	i = -1;
	if (g->m->sky == NULL || g->m->floor == NULL)
		exit(1);
	while(g->m->sky[++i])
		if ((g->m->sky[i] > '9' && g->m->sky[i] != ',')
				|| (g->m->sky[i] < '0' && g->m->sky[i] != ','))
				exit(1);
	i = -1;
	while(g->m->floor[++i])
		if ((g->m->floor[i] > '9' && g->m->floor[i] != ',')
				|| (g->m->floor[i] < '0' && g->m->floor[i] != ','))
				exit(1);
}

void	parse_sky(t_mlx *g)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	g->m->sky_colors = malloc(sizeof(int) * 3);
	while (g->m->sky[++i])
	{
		if (i == 0 && g->m->sky[i] != ',')
			g->m->sky_colors[j] = ft_atoi(g->m->sky);
		if (g->m->sky[i] == ',')
		{
			if (++j == 3 || g->m->sky[++i] == ',')
				exit(1);
			g->m->sky_colors[j] = 
				ft_atoi(ft_substr(g->m->sky, i, ft_strlen(g->m->sky)));
		}
	}
	i = -1;
	while (g->m->sky_colors[++i])
		if (g->m->sky_colors[i] < 0 || g->m->sky_colors[i] > 255)
			exit(1);
	g->m->sky_color = rgb_to_int(g->m->sky_colors[0], g->m->sky_colors[1], 
			g->m->sky_colors[2]);
}

void	parse_floor(t_mlx *g)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	g->m->floor_colors = malloc(sizeof(int) * 3);
	while (g->m->floor[++i])
	{
		if (i == 0 && g->m->floor[i] != ',')
			g->m->floor_colors[j] = ft_atoi(g->m->floor);
		if (g->m->floor[i] == ',')
		{
			if (++j == 3 || g->m->floor[++i] == ',')
				exit(1);
			g->m->floor_colors[j] = 
				ft_atoi(ft_substr(g->m->floor, i, ft_strlen(g->m->floor)));
		}
	}
	i = -1;
	while (g->m->floor_colors[++i])
		if (g->m->floor_colors[i] < 0 || g->m->floor_colors[i] > 255)
			exit(1);
	g->m->floor_color = rgb_to_int(g->m->floor_colors[0], g->m->floor_colors[1], 
			g->m->floor_colors[2]);
}

bool	is_texture_path_valid(char *path)
{
	int fd;
	char *file_type;

	fd = open(path, O_RDONLY);
	file_type = ft_substr(path, ft_strlen(path) - 4, ft_strlen(path));
	if (fd == -1 || ft_strcmp(file_type, ".xpm"))
		return false;
	return true;
}

void	parse_textures(t_mlx *g)
{
	int	i;

	i = -1;
	g->m->texture = malloc(sizeof(char *) * 4);
	while(++i < 4)
		g->m->texture[i] = NULL;
	i = -1;
	while(g->m->cub[++i])
	{
		if (!ft_strncmp(g->m->cub[i], "NO ", 3))
			g->m->texture[0] = ft_substr(g->m->cub[i], 3, ft_strlen(g->m->cub[i]));
		if (!ft_strncmp(g->m->cub[i], "SO ", 3))
			g->m->texture[1] = ft_substr(g->m->cub[i], 3, ft_strlen(g->m->cub[i]));
		if (!ft_strncmp(g->m->cub[i], "WE ", 3))
			g->m->texture[2] = ft_substr(g->m->cub[i], 3, ft_strlen(g->m->cub[i]));
		if (!ft_strncmp(g->m->cub[i], "EA ", 3))
			g->m->texture[3] = ft_substr(g->m->cub[i], 3, ft_strlen(g->m->cub[i]));
	}
	i = -1;
	while(++i < 4)
		if (g->m->texture[i] == NULL
				|| !is_texture_path_valid(g->m->texture[i]))
			exit(1);
}

void parse_values(t_mlx *g)
{
	parse_textures(g);
	parse_colors(g);
	parse_sky(g);
	parse_floor(g);
	/*(void)g;*/
}
