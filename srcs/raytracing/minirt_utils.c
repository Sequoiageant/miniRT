/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:35:45 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/15 13:01:51 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

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

/*t_obj *copy_list(t_obj *head)
{
	t_obj *current = head;	// used to iterate over original list
	t_obj *newList = NULL; // head of the new list
	t_obj *tail = NULL;	// point to last node in new list

	while (current != NULL)
	{
		// special case for the first new Node
		if (newList == NULL)
		{
			newList = (t_obj *)malloc(sizeof(t_obj));
			newList->type = current->type;
			newList->next = NULL;
			tail = newList;
		}
		else
		{
			tail->next = (t_obj *)malloc(sizeof(t_obj));
			tail = tail->next;
			tail->type = current->type;
			tail->next = NULL;
		}
		current = current->next;
	}

	return (newList);
}*/
