/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:04:24 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/11 15:04:25 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

void	put_pixel_img(t_mlx *data, int x, int y, int color);

void	render_gun(t_mlx *mlx)
{
	int				x;
	int				y;
	char			*img_data;
	unsigned int	color;

	x = 0;
	y = 0;
	img_data = mlx->guntexture.addr;
	while (y < mlx->guntexture.h)
	{
		x = 0;
		while (x < mlx->guntexture.w)
		{
			color = *(unsigned int *)(img_data + (y * mlx->guntexture.line_len)
					+ (x * mlx->guntexture.bpp / 8));
			put_pixel_img(mlx, WIDTH - mlx->guntexture.w + x, HEIGHT
				- mlx->guntexture.h + y, color);
			x++;
		}
		y++;
	}
}
