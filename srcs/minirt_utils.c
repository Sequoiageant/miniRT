/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:35:45 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/02 17:57:23 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    char	*dst;

    dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t | r << 8 | g << 16 | b << 24);
}

void	ft_free_tab2(char **tab)
{
	free(tab);
	tab = NULL;
}

float	ft_max(float a, float b)
{
	return ((a > b) ? a : b);
}

float	ft_min(float a, float b)
{
	return ((a < b) ? a : b);
}

float	rad(float alpha)
{
	return (alpha * M_PI / 180);
}
