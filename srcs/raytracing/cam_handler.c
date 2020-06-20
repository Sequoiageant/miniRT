/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:45:05 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 16:35:40 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		choose_cam(int key, t_data *data)
{
	static int	cam_choice = 1;
	t_mlx		mlx;

	mlx = data->mlx;
	if (key == LEFT && cam_choice > 1)
		cam_choice--;
	else if (key == RIGHT && cam_choice < data->cams_set)
		cam_choice++;
	if (cam_choice > 0 && cam_choice <= data->cams_set)
	{
		data->cam_num = cam_choice;
		raytracing(data);
		mlx_put_image_to_window(mlx.mlx_ptr, mlx.mlx_win, mlx.img, 0, 0);
	}
	return (SUCCESS);
}

t_cam	select_cam(t_data data)
{
	while (data.cams)
	{
		if (data.cams->nbr == data.cam_num)
			return (*data.cams);
		data.cams = data.cams->next;
	}
	return (*data.cams);
}
