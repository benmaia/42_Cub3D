#ifndef MAIN_H
#define MAIN_H

typedef struct s_map
{
	int fd;
	char	**map;
	int	x;
	int	y;
}	t_map;

typedef struct s_player
{
	int x;
	int y;
} t_player;

typedef struct s_global
{
	t_map *map;
	t_player *player;
} t_global;

#endif
