#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> 

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

bool	is_file_valid(int argc, char **argv)
{
	char * file_type;
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
	if (!ft_strcmp(file_type, ".cub"))
		return true;
	else
		return false;
}

void	map_parser(int argc, char **argv)
{
	if (!is_file_valid(argc, argv))
	{
		printf("\nPlease select a valid file, only .cub files are accepted\n");
		exit(1);
	}

}

int main(int argc, char **argv)
{
	map_parser(argc, argv);
	printf("keep going\n");
	return 0;
}
