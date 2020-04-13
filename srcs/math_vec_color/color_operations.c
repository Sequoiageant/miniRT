/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:47:47 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/10 19:48:04 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	mult_col_double(t_col col, double mult)
{
	return (int_to_col(col.r * mult, col.g * mult, col.b * mult));
}

t_col	mult_col(t_col col1, t_col col2)
{
	return (int_to_col(col1.r * (col2.r / 255.0), col1.g * (col2.g / 255.0),
		col1.b * (col2.b / 255.0)));
}

t_col	add_colors(t_col col, t_col add)
{
	t_col new_col;

	new_col.r = ft_min(col.r + add.r, 255);
	new_col.g = ft_min(col.g + add.g, 255);
	new_col.b = ft_min(col.b + add.b, 255);
	return (new_col);
}

t_col	sub_colors(t_col col, t_col sub)
{
	t_col new_col;

	new_col.r = ft_min(col.r - sub.r, 255);
	new_col.g = ft_min(col.g - sub.g, 255);
	new_col.b = ft_min(col.b - sub.b, 255);
	return (new_col);
}

t_col	ft_min_col(t_col col)
{
	t_col new_col;

	new_col.r = ft_min(col.r, 255);
	new_col.g = ft_min(col.g, 255);
	new_col.b = ft_min(col.b, 255);
	return (new_col);
}
