/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:53:12 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/10 19:47:27 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int		color_encode(t_col col)
{
	return (col.r << 16 | col.g << 8 | col.b);
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
