#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> 
# include <fcntl.h>
#include "main.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	s_len;
	char	*new;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < len)
		new = (char *)malloc(sizeof(char) * (s_len + 1));
	else
		new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			new[j++] = s[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i]
		&& (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	find_i(char *saved)
{
	int	i;

	i = 0;
	while (saved[i])
	{
		if (saved[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

static int	has_new_line(char *saved)
{
	int	i;

	i = 0;
	while (saved[i])
	{
		if (saved[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i])
		i++;
	new = (char *)malloc((i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

static char	*return_line(char **saved)
{
	int		i;
	char	*line;
	char	*temp;

	if (!*saved || **saved == '\0')
		return (NULL);
	i = find_i(*saved);
	if (has_new_line(*saved))
	{
		line = ft_substr(*saved, 0, i + 1);
		temp = ft_substr(*saved, i + 1, ft_strlen(*saved));
		free (*saved);
		*saved = temp;
		if (**saved != '\0')
			return (line);
	}
	else
		line = ft_strdup(*saved);
	free (*saved);
	*saved = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*saved[256];
	char		*temp;
	int			ret;

	if (fd < 0 || fd > 256 || 10 < 1)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (10 + 1));
	if (!buf)
		return (NULL);
	ret = read(fd, buf, 10);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (saved[fd] == NULL)
			saved[fd] = ft_strdup("");
		temp = ft_strjoin(saved[fd], buf);
		free (saved[fd]);
		saved[fd] = temp;
		if (has_new_line(saved[fd]))
			break ;
		ret = read(fd, buf, 10);
	}
	free (buf);
	return (return_line(&saved[fd]));
}


static int	nb_words(const char *str, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c && flag == 0)
		{
			flag = 1;
			i++;
		}
		else if (*str == c)
			flag = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (finish - start + 1));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = (char **)malloc(sizeof(char *) * (nb_words(s, c) + 1));
	if (!s || !split)
		return (NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}



void	read_map(t_global *g)
{
	char	*str;
	char	*buf;
	char	*tmp;

	str = ft_strdup("");
	buf = get_next_line(g->map->fd);
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
		buf = get_next_line(g->map->fd);
	}
	g->map->map = ft_split(str, '\n');
	free(str);
	str = NULL;
	free(buf);
	buf = NULL;
}


bool	is_file_valid(int argc, char **argv, t_global *g)
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
	g->map->fd = open(argv[1], O_RDONLY);
	if (g->map->fd == -1 || ft_strcmp(file_type, ".cub"))
		return false;
	return true;
}

bool	check_map_playble(t_global *g)
{
	int			i;
	int			j;
	static int	p = 0;

	i = -1;
	while (g->map->map[++i])
	{
		j = -1;
		while (g->map->map[i][++j])
		{
			if (g->map->map[i][j] == 'N' || g->map->map[i][j] == 'S' || g->map->map[i][j] == 'W' || g->map->map[i][j] == 'E')
			{
				p++;
				g->player->x = i;
				g->player->y = j;
			}
		}
	}
	if (p != 1)
	{
		printf("To many start positions\n");
		return false;
	}
	return true;
}

void	map_parser(int argc, char **argv, t_global *g)
{
	if (is_file_valid(argc, argv, g) == false)
	{
		printf("\nPlease select a valid file, only .cub files are accepted\n");
		exit(1);
	}
	read_map(g);
	if (check_map_playble(g))
		exit(1);

}

int main(int argc, char **argv)
{
	t_global g;
	int i = -1;
	
	g.map = malloc(sizeof(t_map));
	g.player = malloc(sizeof(t_player));
	printf("start\n");
	map_parser(argc, argv, &g);


	while (g.map->map[++i])
		printf("Mapa %s\n", g.map->map[i]);
	printf("Player position x = %d, y = %d\n", g.player->x, g.player->y);
	return 0;
}
