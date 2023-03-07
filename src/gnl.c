/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:27:57 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/07 18:31:18 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

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
