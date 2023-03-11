/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:44:30 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/11 12:58:22 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

void	read_map(t_mlx *g)
{
	char	*str;
	char	*buf;
	char	*tmp;

	str = ft_strdup("");
	buf = get_next_line(g->m->fd);
	while (buf != NULL)
	{
		tmp = ft_strjoin(str, buf);
		free(str);
		str = tmp;
		free(buf);
		buf = get_next_line(g->m->fd);
	}
	g->m->cub = ft_split(str, '\n');
	free(str);
	str = NULL;
	free(buf);
	buf = NULL;
}


bool	is_file_valid(int argc, char **argv, t_mlx *g)
{
	char *file_type;
	int i;
	int counter;

	file_type = ft_substr(argv[argc - 1],
			ft_strlen(argv[argc - 1])- 4, ft_strlen(argv[argc - 1]));
	i = -1;
	counter = 0;
	while (argv[argc - 1][++i])
	{
		if (argv[argc - 1][i] == '.')
			counter++;
		if (counter >= 2 ||
				(argv[argc -1][i] <= 32 && argv[argc - 1][i] >= 127))
			return false;
	}
	g->m->fd = open(argv[1], O_RDONLY);
	if (g->m->fd == -1 || ft_strcmp(file_type, ".cub"))
	{
		free (file_type);
		return false;
	}
	free (file_type);
	return true;
}

bool	check_map_playble(t_mlx *g)
{
	int			i;
	int			j;

	i = -1;
	while (g->m->map[++i])
	{
		j = -1;
		while (g->m->map[i][++j])
		{
			if (g->m->map[i][j] == 'N' || g->m->map[i][j] == 'S'
					|| g->m->map[i][j] == 'W' || g->m->map[i][j] == 'E')
			{
				g->m->orientation = g->m->map[i][j];
				g->m->p_x = i;
				g->m->p_y = j;
				g->m->players++;
			}
		}
		if (j > g->m->width)
			g->m->width = j;
	}
	if (i > g->m->height)
		g->m->height = i;
	return true;
}

bool	is_texture_path_valid(char *path)
{
	int fd;
	char *file_type;

	fd = open(path, O_RDONLY);
	file_type = ft_substr(path, ft_strlen(path) - 4, ft_strlen(path));
	if (fd == -1 || ft_strcmp(file_type, ".xpm"))
	{
		free (file_type);
		return false;
	}
	free (file_type);
	return true;
}

void	map_parser(int argc, char **argv, t_mlx *g)
{
	g->m = malloc(sizeof(t_map));
	init_map_struct(g);
	if (is_file_valid(argc, argv, g) == false)
		wrong_map(g);
	read_map(g);
	parse_values(g);
	parse_map(g);
	if (!check_map_playble(g) || g->m->players != 1)
		wrong_map(g);
}
