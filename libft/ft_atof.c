/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:58:17 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/19 19:44:52 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	e;
	double	d;
	int		len;
	short	sign;

	e = (double)ft_atoi(str);
	sign = 1;
	if (str[0] == '-')
		sign = -sign;
	if (str[0] == '-' || str[0] == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '.')
		str++;
	len = 0;
	d = 0.0;
	while (str[len] >= '0' && str[len] <= '9')
	{
		d = d * 10 + str[len] - 48;
		len++;
	}
	d /= pow(10, len);
	return ((sign < 0) ? -(-e + d) : e + d);
}
