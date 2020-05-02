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

double	ft_norm_vec(double *vec, int dim)
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

double	ft_norm_vec2(double *vec, int dim)
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

double 	ft_dot_product(double *u, double *v, int dim)
{
    int		i;
    double	result;

    i = 0;
    result = 0.0;
    while (i < dim)
    {
        result += u[i] * v[i];
        i++;
    }
    return (result);
}

void	cross_product3(double *u, double *v, double *p)
{
	p[0] = v[2] * u[1] - v[1] * u[2]; 
	p[1] = v[0] * u[2] - v[2] * u[0]; 
	p[2] = v[1] * u[0] - v[0] * u[1]; 
}

double	*mult_vec3(double *u, double m)
{
	double *mult;

	mult[0] = m * u[0]; 
	mult[1] = m * u[1]; 
	mult[2] = m * u[2]; 
	return (mult);
}

void	ft_add_vec(double *u, double *v, double *p, int dim)
{
	int		i;

	i = 0;
	while (i < dim)
	{
		p[i] = u[i] + v[i];
		i++;
	}
}

void	ft_sub_vec(double *u, double *v, double *p, int dim)
{
	int		i;

	i = 0;
	while (i < dim)
	{
		p[i] = u[i] - v[i];
		i++;
	}
}

void	ft_normalize(double *vec, int dim)
{
	double norm;

	norm = ft_norm_vec(vec, dim);
	if (norm != 1 && norm != 0)
	{
		vec[0] /= norm;
		vec[1] /= norm;
		vec[2] /= norm;
	}
}

double	*ft_get_normalize(double *vec, int dim)
{
	double *n;

	n = vec;
	ft_normalize(n, dim);
	return (n);
}
