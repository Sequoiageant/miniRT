/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 17:29:56 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 16:23:35 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_close(t_data *data)
{
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
	mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
	free_minirt(data);
	free(data->mlx.mlx_ptr);
	exit(EXIT_SUCCESS);
}

int	key_event(int key, t_data *data)
{
	ft_putnbr(key);
	ft_putendl("");
	if (key == LEFT || key == RIGHT)
		choose_cam(key, data);
	else if (key == ESC)
		ft_close(data);
	return (0);
}

int	launch_window(t_data *data)
{
	t_mlx	mlx;
	t_win	win;

	if ((mlx.mlx_ptr = mlx_init()) == NULL)
		return (FAILURE);
	mlx_get_screen_size(mlx.mlx_ptr, &mlx.max_w, &mlx.max_h);
	data->win.w = ft_min(data->win.w, mlx.max_w);
	data->win.h = ft_min(data->win.h, mlx.max_h);
	win = data->win;
	mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, win.w, win.h, "miniRT");
	if (mlx.mlx_win == NULL)
		return (FAILURE);
	if ((mlx.img = mlx_new_image(mlx.mlx_ptr, win.w, win.h)) == NULL)
		return (FAILURE);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_len, &mlx.end);
	if (mlx.addr == NULL)
		return (FAILURE);
	data->mlx = mlx;
	mlx_hook(mlx.mlx_win, 3, (1 << 1), key_event, data);
	mlx_hook(mlx.mlx_win, 17, (1L << 17), ft_close, data);
	data->cam_num = 1;
	raytracing(data);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.mlx_win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (SUCCESS);
}

int	save_image(t_data *data)
{
	t_mlx	mlx;
	t_win	win;

	if ((mlx.mlx_ptr = mlx_init()) == NULL)
		return (FAILURE);
	mlx_get_screen_size(mlx.mlx_ptr, &mlx.max_w, &mlx.max_h);
	data->win.w = ft_min(data->win.w, mlx.max_w);
	data->win.h = ft_min(data->win.h, mlx.max_h);
	win = data->win;
	if ((mlx.img = mlx_new_image(mlx.mlx_ptr, win.w, win.h)) == NULL)
		return (FAILURE);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_len, &mlx.end);
	if (mlx.addr == NULL)
		return (FAILURE);
	data->mlx = mlx;
	data->cam_num = 1;
	raytracing(data);
	if (save_bmp((unsigned char*)mlx.addr, data->win) == FAILURE)
		return (FAILURE);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img);
	free(data->mlx.mlx_ptr);
	return (SUCCESS);
}
