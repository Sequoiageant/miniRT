/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_forms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:48:03 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/04 17:27:59 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_draw_sphere(t_data *data)
{
	double phi;
	double theta;
	int R;
	int x;
	int y;
	int z;

	R = 150;
	phi = 1;
	while (phi <= 360)
	{
		theta = -90;
		while (theta <= 90)
		{
			x = cos(theta) * cos(phi) * R;
			y = cos(theta) * sin(phi) * R;
			z = sin(theta) * R;
			ft_pixel_put(data, x + 400, y + 300, 0xFFFF00);
			theta += 0.5;
		}
		phi++;
	}
	mlx_put_image_to_window(data, data->mlx_win, data->img, 0, 0);
}

void	ft_draw_circle(t_data *data)
{
	double	angle;
	int		r;
	int 	x;
	int 	y;

	r = 200;
	while (r > 0)
	{
		angle = 0;
		while (angle < 360)
		{
			x = r * cos(angle * M_PI / 180);
			y = r * sin(angle * M_PI / 180);
			// mlx_pixel_put(data->mlx_ptr, data->mlx_win, x + 300, y + 300, 0.1*color.r*color.g*color.b);
			ft_pixel_put(data, x + 300, y + 300, create_trgb(255, (angle/360)*255, (angle/360)*255, 0));
			angle += 0.1;
		}
		r--;
	}
	mlx_put_image_to_window(data, data->mlx_win, data->img, 0, 0);
}

void	ft_draw_square(t_data *data)
{
	// t_color	color;
	int		x;
	int		y;

	x = 300;
	while (x < 580)
	{
		y = 120;
		while (y < 460)
		{
			ft_pixel_put(data, x, y, 0x00FF0000);
			// mlx_pixel_put(data->mlx_ptr, data->mlx_win, i, j, color.r*color.g*color.b);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data, data->mlx_win, data->img, 0, 0);
}

void	ft_draw_triangle(t_data *data)
{
	// t_color	color;
	int		x;
	int		y;

	x = 400;
	while (x < 580)
	{
		y = 400;
		while (y < x)
		{
			ft_pixel_put(data, x, y, 0xFFFF00);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data, data->mlx_win, data->img, 0, 0);
}

void	ft_draw_hex(t_data *data)
{
	int length=150, i=0, j=0, k, l;

	for(i = 1, k=length, l=2*length-1; i<length; i++, k--, l++)
	{
		for(j = 0; j < 3*length; j++)
		{
			if(j>=k && j<=l)
				ft_pixel_put(data, j, i, 0x00FF00);
		}
	}

	for(i = 0, k=1, l=3*length-2; i<length; i++, k++, l--)
	{
		for(j=0; j<3*length;j++)
		{
			if(j>=k && j<=l)
				ft_pixel_put(data, j, i, 0xFFFF00);
		}
	}
	mlx_put_image_to_window(data, data->mlx_win, data->img, 0, 0);
}
