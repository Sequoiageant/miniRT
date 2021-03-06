/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:35:45 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 11:43:18 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_max(double a, double b)
{
	return ((a > b) ? a : b);
}

double	ft_min(double a, double b)
{
	return ((a < b) ? a : b);
}

double	deg_to_rad(double alpha)
{
	return (alpha * PI / 180);
}

double	rad_to_deg(double alpha)
{
	return (alpha * 180 / PI);
}

double	normalize_and_markout(double to_mod, double denom)
{
	double modified;

	modified = to_mod / denom;
	modified = ft_min(modified, 1.0);
	modified = ft_max(0.0, modified);
	return (modified);
}
