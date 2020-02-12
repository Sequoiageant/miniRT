/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:57:34 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/10 19:53:14 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ft_norm_vec(float *vec, int dim)
{
	int		i;
	double	norm;

	i = 0;
	norm = 0.0;
	while (i < dim)
	{
		norm += vec[i] * vec[i];
		i++;
	}
	return (sqrt(norm));
}

float	ft_norm_vec2(float *vec, int dim)
{
	int		i;
	double	norm;

	i = 0;
	norm = 0.0;
	while (i < dim)
	{
		norm += vec[i] * vec[i];
		i++;
	}
	return (norm);
}

float 	ft_dot_product(float *u, float *v, int dim)
{
    int		i;
    float	result;

    i = 0;
    result = 0.0;
    while (i < dim)
    {
        result += u[i] * v[i];
        i++;
    }
    return (result);
}

void	ft_cross_product3(float *u, float *v, float *p)
{
	p[0] = v[2] * u[1] - v[1] * u[2]; 
	p[1] = v[0] * u[2] - v[2] * u[0]; 
	p[2] = v[1] * u[0] - v[0] * u[1]; 
}

float	*ft_mult_vec3(float *u, float m)
{
	float *mult;

	mult[0] = m * u[0]; 
	mult[1] = m * u[1]; 
	mult[2] = m * u[2]; 
	return (mult);
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

float	*ft_get_normalize(float *vec, int dim)
{
	float *n;

	n = vec;
	ft_normalize(n, dim);
	return (n);
}
