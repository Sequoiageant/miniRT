/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:45:05 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/18 18:41:42 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*int	search_list(int cam_num, t_data data)
{
	while (data->cams)
	{
		if (data->cams->nbr == cam_num)
			return (1) ;
		data->cams = data->cams->next;
	}
	return (0);
}*/

int choose_cam(int key, t_data *data)
{
	static int cam_choice = 1;
	t_mlx	mlx;

	mlx = data->mlx;
	if(key == LEFT && cam_choice > 1)
		cam_choice--;
	else if(key == RIGHT && cam_choice < data->cams_set)
		cam_choice++;
	if (cam_choice > 0 && cam_choice <= data->cams_set)
	{
		// search_list(cam_choice, data);
		data->cam_num = cam_choice;
		// mlx_clear_window(mlx.mlx_ptr, mlx.mlx_win);
		// reset_image(data);
		raytracing(data);
		mlx_put_image_to_window(mlx.mlx_ptr, mlx.mlx_win, mlx.img, 0, 0);
	}
	printf("%d\n", data->cam_num);
	return(0);
}
