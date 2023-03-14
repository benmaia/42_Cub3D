/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:09:04 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/12 13:13:26 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"


int check_empty(char c)
{
	if (c == 'N' ||c == 'S' || c == 'W'|| c == 'E' || c == '0')
		return(1);
	return(0);
}		

int	draw_map(t_mlx *mlx)
{
	int	square_size;
	int	x;
	int	y;
	int	col;
	int	row;

	square_size = sqrt((WIDTH * HEIGHT) / 4) / mlx->m->width;;
	row = -1;
	while (mlx->m->minimap[++row])
	{
		col = -1;
		while (mlx->m->minimap[row][++col])
		{
			x = col * square_size;
			y = row * square_size;
			if (mlx->m->minimap[row][col] == '1')
				mlx_square(mlx, x, y, square_size, 0x000000);
			else if (check_empty(mlx->m->minimap[row][col]))
				mlx_square(mlx, x, y, square_size, 0xFFFFFF);
			else
				continue;
		}
	}
	return(square_size);
}

void	displayMap(t_mlx *mlx)
{
	double	minimap_pos_x;
	double	minimap_pos_y;
	int sq;
	float scale;
	sq = draw_map(mlx);
	scale = (float)sq / (float)TILES;
	minimap_pos_x = mlx->p->x * scale - sq / 8;
	minimap_pos_y = mlx->p->y * scale - sq / 8;
	mlx_square(mlx, minimap_pos_x , minimap_pos_y, sq / 2 , 0xFF0000);
	mlx_line_to(mlx, minimap_pos_x + sq /8 , minimap_pos_y + sq / 8, minimap_pos_x + mlx->p->dx
		* 5, minimap_pos_y + mlx->p->dy * 5, rgb_to_int(255, 123, 11));
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->img, 0, 0);
}
