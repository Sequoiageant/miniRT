/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:18:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/01/31 15:18:47 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"


/*	ALGO :
** Place the eye and the frame as desired (1)
** For each pixel on the screen
**     Determine the square on the grid corresponding to this pixel (2)
**     Determine the color seen through that square (3)
**     Paint the pixel with that color (4)
*/
void	ft_raytracing(t_data *data, t_win *win)
{
/*	int	cam_x = 0;
	double	cam_y = 0;
	double	cam_z = 20;	
	double	cam_or_x = 0;
	double	cam_or_y = 0;
	double	cam_or_z = 1;*/
	// int	fov = 0;
	// double d[] = [0, 0, 1];
	// double O[] = [0, 0, 0];
	// double r[] = [0, 0, 0];
	double	xo = 0;
	double	yo = 0;	
	int	x = 0;
	int	y = 0;
	double	i;
	double	j;

// u=l+(r−l)(i+0.5)/nx;
// v=b+(t−b)(j+0.5)/ny,



	i = 0;
	while (i < win->w)
	{
		j = 0;
		while (j < win->h)
		{
			xo = (i + 0.5) / win->w;
			yo = (j + 0.5) / win->h;
			x = xo * win->w;
			y = yo * win->h;

			ft_pixel_put(data, x, y, 0xFFFF00);
			j++;
		}
		i++;
	}
	ft_putnbr(i * j);
	mlx_put_image_to_window(data, data->mlx_win, data->img, 0, 0);


}

/*void	ft_raytracing(t_data *data, t_win *win)
{
int	cam_x = 0;
	double	cam_y = 0;
	double	cam_z = 20;	
	double	cam_or_x = 0;
	double	cam_or_y = 0;
	double	cam_or_z = 1;
	// int	fov = 0;
	// double d[] = [0, 0, 1];
	// double O[] = [0, 0, 0];
	double	xo = 0;
	double	yo = 0;	
	int	x = 0;
	int	y = 0;
	double	i;
	double	j;

	i = 0;
	while (i < win->w)
	{
		j = 0;
		while (j < win->h)
		{
			xo = (i + 0.5) / 2;
			yo = (j + 0.5) / 2;
			x = xo * 2 - 1;
			y = yo * 2 - 1;

			ft_pixel_put(data, x, y, 0xFFFF00);
			j++;
		}
		i++;
	}
	ft_putnbr(i * j);
	mlx_put_image_to_window(data, data->mlx_win, data->img, 0, 0);


}
*/