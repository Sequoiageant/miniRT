/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 20:47:28 by julien            #+#    #+#             */
/*   Updated: 2020/04/08 17:18:49 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_list(t_obj *objlst)
{
	if (objlst)
	{
		while (objlst)
		{
			printf("	-->type: %d\n", objlst->type);
			objlst = objlst->next;
		}
	}
	else
		printf("%s\n", "LISTE VIDE");
}

void free_objlist(t_obj **objlst)
{
	t_obj *tmp;

	while (*objlst != NULL)
	{
		tmp = *objlst;
		*objlst = (*objlst)->next;
		free(tmp);
		tmp = NULL;
	}
	*objlst = NULL;
}

void free_camlist(t_cam **camlst)
{
	t_cam *tmp;

	while (*camlst != NULL)
	{
		tmp = *camlst;
		*camlst = (*camlst)->next;
		free(tmp);
		tmp = NULL;
	}
	*camlst = NULL;
}

void free_lightlist(t_light **lightlst)
{
	t_light *tmp;

	while (*lightlst != NULL)
	{
		tmp = *lightlst;
		*lightlst = (*lightlst)->next;
		free(tmp);
		tmp = NULL;
	}
	*lightlst = NULL;
}

void free_minirt(t_data *data)
{
	if (data->objlst_set)
		free_objlist(&data->objlst);
	if (data->lights_set)
		free_lightlist(&data->lights);
	if (data->cams_set)
		free_camlist(&data->cams);
}

int ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
	// print_list(data->objlst);
	free_minirt(data);
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
		return (FAILURE);
	if ((mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, win.w, win.h, "miniRT")) == NULL)
		return (FAILURE);
	mlx.img = mlx_new_image(mlx.mlx_ptr, win.w, win.h);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	data->mlx = mlx;
	mlx_hook(mlx.mlx_win, 3, 1L << 1, key_event, data);
	mlx_hook(mlx.mlx_win, 17, 1L << 17, ft_close, data);
	data->cam_num = 1;
	ft_raytracing(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_win, data->mlx.img, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (SUCCESS);
}

int	ft_save_image(t_data *data)
{
	t_mlx	mlx;
	t_win	win;

	win = data->win;
	if ((mlx.mlx_ptr = mlx_init()) == NULL)
		return (FAILURE);
	mlx.img = mlx_new_image(mlx.mlx_ptr, win.w, win.h);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	data->mlx = mlx;
	data->cam_num = 1;
	ft_raytracing(data);
	if (save_bmp((unsigned char*)mlx.addr, data->win) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
