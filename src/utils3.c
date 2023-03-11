/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:55:24 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/11 21:58:55 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

char	*ft_strcpy(char *dest, char *src)
{
	char	*p;
	int		i;

	p = dest;
	i = -1;
	while (src[++i] != '\0')
		p[i] = src[i];
	return (dest);
}

void	ft_bzero(void *str, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = str;
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	ptr = malloc(size * n);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * n);
	return (ptr);
}

void	*ft_memset(void *str, int c, size_t count)
{
	char	*dest;

	dest = (char *)str;
	while (0 < count)
	{
		dest[count - 1] = c;
		count--;
	}
	return (str);
}
