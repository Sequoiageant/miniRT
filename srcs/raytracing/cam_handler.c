/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 20:52:12 by julien            #+#    #+#             */
/*   Updated: 2020/05/04 18:44:10 by julnolle         ###   ########.fr       */
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

	if(key == LEFT && cam_choice > 1)
		cam_choice--;
	else if(key == RIGHT && cam_choice < data->cams_set)
		cam_choice++;
	if (cam_choice > 0 && cam_choice < data->cams_set)
	{
		// search_list(cam_choice, data);
		data->cam_num = cam_choice;
		// mlx_clear_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
		reset_image(data);
		raytracing(data);
	}
	printf("%d\n", data->cam_num);
	return(0);
}
