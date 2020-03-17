/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:53:12 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/06 11:35:47 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rgb_to_int(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

void	init_color(t_col *col)
{
	col->r = 0;
	col->g = 0;
	col->b = 0;
}

t_col	int_to_col(int r, int g, int b)
{
	t_col	col;

	col.r = r;
	col.g = g;
	col.b = b;
	return (col);
}

t_col	char_to_col(char *r, char *g, char *b)
{
	t_col	col;

	col.r = ft_atoi(r);
	col.g = ft_atoi(g);
	col.b = ft_atoi(b);
	return (col);
}

t_col	mult_col_double(t_col col, double mult)
{
	return (int_to_col(col.r * mult, col.g * mult, col.b * mult));
}

t_col	mult_col(t_col col1, t_col col2)
{
	return (int_to_col(col1.r * (col2.r / 255.0), col1.g * (col2.g / 255.0), col1.b * (col2.b / 255.0)));
}

int		color_encode(t_col col)
{
	return(col.r << 16 | col.g << 8 | col.b);
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
