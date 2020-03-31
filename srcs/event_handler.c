/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 20:47:28 by julien            #+#    #+#             */
/*   Updated: 2020/03/24 21:00:38 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
	// print_list(data->objlst);
	free(data->objlst);
	data->objlst = NULL;
	// print_list(data->objlst);
	exit(EXIT_SUCCESS);
}

int key_event(int key, t_data *data)
{
	ft_putnbr(key);
	ft_putendl("");
	if(key == LEFT || key == RIGHT)
		choose_cam(key, data);
	else if(key == ESC)
		ft_close(data);
	return(0);
}

int	ft_launch_window(t_data *data)
{
	t_mlx	mlx;
	t_win	win;

	win = data->win;
	if ((mlx.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, win.w, win.h, "miniRT")) == NULL)
		return (EXIT_FAILURE);
	mlx.img = mlx_new_image(mlx.mlx_ptr, win.w, win.h);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	data->mlx = mlx;
	mlx_hook(mlx.mlx_win, 3, 1L << 1, key_event, data);
	mlx_hook(mlx.mlx_win, 17, 1L << 17, ft_close, data);
	data->cam_num = 1;
	ft_raytracing(data);
	mlx_loop(mlx.mlx_ptr);
	return (EXIT_SUCCESS);
}
