/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:58:17 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/06 10:13:02 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_simple_atoi(const char *str, double *len)
{
	int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - 48;
		str++;
		(*len)++;
	}
	return (res);
}

double	ft_atof(const char *str)
{
	double	e;
	double	d;
	double	len;

	e = (double)ft_atoi(str);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '.')
		str++;
	d = (double)ft_simple_atoi(str, &len) / pow(10, len);
	return (e < 0 ? -(-e + d) : e + d);
}
