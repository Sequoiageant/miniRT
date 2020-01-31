/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:35:45 by julnolle          #+#    #+#             */
/*   Updated: 2020/01/31 11:59:19 by julnolle         ###   ########.fr       */
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


double ft_dot_product(double *v, double *u, int dim)
{
    int		i;
    double	result;

    i = 0;
    result = 0.0;
    while (i < dim)
    {
        result += v[i]*u[i];
        i++;
    }
    return (result);
}