/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:35:45 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/06 10:31:16 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_atoi2(char **str)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while ((**str >= 9 && **str <= 13) || **str == ' ')
		(*str)++;
	if ((*str)[0] == '+' || (*str)[0] == '-')
		i++;
	while ((*str)[i] >= '0' && (*str)[i] <= '9')
	{
		res = res * 10 + (*str)[i] - 48;
		i++;
	}
	(*str) += i;
	return ((*str)[0] == '-' ? -res : res);
}

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


float 	ft_dot_product(float *u, float *v, int dim)
{
    int		i;
    float	result;

    i = 0;
    result = 0.0;
    while (i < dim)
    {
        result += u[i]*v[i];
        i++;
    }
    return (result);
}

void	ft_cross_product(float *u, float *v, float *p)
{
	p[0] = v[1] * u[2] - v[2] * u[1]; 
	p[1] = v[0] * u[2] - v[2] * u[0]; 
	p[2] = v[0] * u[1] - v[1] * u[0]; 
}

void	ft_add_vec(float *u, float *v, float *p, int dim)
{
	int		i;

	i = 0;
	while (i < dim)
	{
		p[i] = u[i] + v[i];
		i++;
	}
}

void	ft_sub_vec(float *u, float *v, float *p, int dim)
{
	int		i;

	i = 0;
	while (i < dim)
	{
		p[i] = u[i] - v[i];
		i++;
	}
}

float	ft_norm_vec(float *vec, int dim)
{
	int		i;
	double	norm;

	i = 0;
	norm = 0.0;
	while (i < dim)
	{
		norm += pow(vec[i], 2);
		i++;
	}
	return (sqrt(norm));
}

void	ft_normalize(float *vec, int dim)
{
	float norm;

	norm = ft_norm_vec(vec, dim);
	if (norm != 1 && norm != 0)
	{
		vec[0] /= norm;
		vec[1] /= norm;
		vec[2] /= norm;
	}
}

int		create_trgb(int t, int r, int g, int b)
{
	return(b << 24 | g << 16 | r << 8 | t);
}
