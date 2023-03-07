/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:44:30 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/07 18:59:43 by bmiguel-         ###   ########.fr       */
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
		if (!ft_strcmp(buf, "\n"))
		{
			printf("Invalid map\n");
			exit(1);
		}
		tmp = ft_strjoin(str, buf);
		free(str);
		str = tmp;
		free(buf);
		buf = get_next_line(g->m->fd);
	}
	g->m->map = ft_split(str, '\n');
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
		return false;
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
			if (g->m->map[i][j] == 'N' || g->m->map[i][j] == 'S' || g->m->map[i][j] == 'W' || g->m->map[i][j] == 'E')
			{
				g->m->orientation = g->m->map[i][j];
				g->p->x = i;
				g->p->y = j;
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

void	map_parser(int argc, char **argv, t_mlx *g)
{
	g->m = malloc(sizeof(t_map));
	if (is_file_valid(argc, argv, g) == false)
	{
		printf("\nPlease select a valid file, only .cub files are accepted\n");
		exit(1);
	}
	read_map(g);
	if (check_map_playble(g) || g->m->players != 1)
		exit(1);

}
