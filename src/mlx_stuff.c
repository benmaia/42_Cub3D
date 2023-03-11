/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:03:24 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/11 15:03:25 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

void	img_pix_put(t_mlx *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bits_per_pixel - 8;
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bits_per_pixel - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	rgb_to_int(int r, int g, int b)
{
	int	c;

	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	return (c);
}

int	ft_exit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx_destroy_image(mlx->ptr, mlx->guntexture.img_ptr);
	mlx_destroy_image(mlx->ptr, mlx->textures[0].img_ptr);
	mlx_destroy_image(mlx->ptr, mlx->textures[1].img_ptr);
	mlx_destroy_image(mlx->ptr, mlx->textures[2].img_ptr);
	mlx_destroy_image(mlx->ptr, mlx->textures[3].img_ptr);
	free(mlx->p);
	free(mlx->ptr);
	free_map(mlx);
	exit(0);
	return (0);
}

void	load_textures(t_mlx *mlx)
{
	mlx->textures[0].img_ptr = mlx_xpm_file_to_image(mlx->ptr,
			mlx->m->texture[0], &mlx->textures[0].w, &mlx->textures[0].h);
	mlx->textures[0].addr = mlx_get_data_addr(mlx->textures[0].img_ptr,
			&mlx->textures[0].bpp, &mlx->textures[0].line_len,
			&mlx->textures[0].endian);
	mlx->textures[1].img_ptr = mlx_xpm_file_to_image(mlx->ptr,
			mlx->m->texture[1], &mlx->textures[1].w, &mlx->textures[1].h);
	mlx->textures[1].addr = mlx_get_data_addr(mlx->textures[1].img_ptr,
			&mlx->textures[1].bpp, &mlx->textures[1].line_len,
			&mlx->textures[1].endian);
	mlx->textures[2].img_ptr = mlx_xpm_file_to_image(mlx->ptr,
			mlx->m->texture[2], &mlx->textures[2].w, &mlx->textures[2].h);
	mlx->textures[2].addr = mlx_get_data_addr(mlx->textures[2].img_ptr,
			&mlx->textures[2].bpp, &mlx->textures[2].line_len,
			&mlx->textures[2].endian);
	mlx->textures[3].img_ptr = mlx_xpm_file_to_image(mlx->ptr,
			mlx->m->texture[3], &mlx->textures[3].w, &mlx->textures[3].h);
	mlx->textures[3].addr = mlx_get_data_addr(mlx->textures[3].img_ptr,
			&mlx->textures[3].bpp, &mlx->textures[3].line_len,
			&mlx->textures[3].endian);
	mlx->guntexture.img_ptr = mlx_xpm_file_to_image(mlx->ptr,
			"./assets/gun0.xpm", &mlx->guntexture.w, &mlx->guntexture.h);
	mlx->guntexture.addr = mlx_get_data_addr(mlx->guntexture.img_ptr,
			&mlx->guntexture.bpp, &mlx->guntexture.line_len,
			&mlx->guntexture.endian);
}

void	init_libmlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win_x = WIDTH;
	mlx->win_y = HEIGHT;
	mlx->mlx_win = mlx_new_window(mlx->ptr, mlx->win_x, mlx->win_y, "Cub3D");
	mlx->img = mlx_new_image(mlx->ptr, mlx->win_x, mlx->win_y);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	mlx_hook(mlx->mlx_win, 6, (1L << 6), &mouse_hook, mlx);
	mlx_hook(mlx->mlx_win, ON_KEYDOWN, (1L << 0), key_hook, mlx);
	mlx_hook(mlx->mlx_win, 17, (1L << 17), ft_exit, mlx);
	mlx_mouse_hide(mlx->ptr, mlx->mlx_win);
	load_textures(mlx);
}
