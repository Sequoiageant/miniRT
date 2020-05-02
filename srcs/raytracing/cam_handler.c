/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 20:52:12 by julien            #+#    #+#             */
/*   Updated: 2020/03/24 20:53:00 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	search_list(int cam_num, t_data data)
{
	while (data.cams)
	{
		if (data.cams->nbr == cam_num)
		{
			return (1);
		}
		data.cams = data.cams->next;
	}
	return (0);
}

int choose_cam(int key, t_data *data)
{
	static int cam_num = 1;

	if(key == LEFT)
		cam_num--;
	else if(key == RIGHT)
		cam_num++;
	if (cam_num > 0)
	{
		if (search_list(cam_num, *data) == 1)
			data->cam_num = cam_num;
	}
	if (cam_num < data->cam_num)
	{
		if (search_list(cam_num, *data) == 1)
			data->cam_num = cam_num;
	}
	raytracing(data);
	printf("%d\n", cam_num);
	return(0);
}
