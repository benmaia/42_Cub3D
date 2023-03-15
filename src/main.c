/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:07:57 by bmiguel-          #+#    #+#             */
/*   Updated: 2023/03/15 20:21:26 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Cub3d.h"

int	refresh_screen(t_mlx *mlx)
{
	cast_rays(mlx);
	render_gun(mlx);
	if (mlx->map_enabled)
		displaymap(mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->img, 0, 0);
	mlx_do_sync(mlx->ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc > 2)
	{
		printf("Too many arguments\n");
		exit(1);
	}
	map_parser(argc, argv, &mlx);
	init_libmlx(&mlx);
	mlx.p = init_player(mlx.p, mlx.m);
	refresh_screen(&mlx);
	mlx_loop(mlx.ptr);
	free_map(&mlx);
	return (1);
}
