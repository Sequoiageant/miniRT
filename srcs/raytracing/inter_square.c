/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:30:25 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/18 15:49:46 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_pl_square(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3	origin;
	t_vec3	p0;
	double	denom;

	p0 = objlst->u_obj.sq.p0;
	origin = inter->origin;
	denom = dot_product3(*ray, inter->normal);
	if (fabs(denom) > EPSILON)
	{
		inter->t = dot_product3(sub_vec3(p0, origin), inter->normal) / denom;
		inter->pos = add_vec3(origin, multby_vec3(ray, inter->t));
		if (inter->t >= 0.0 && inter->t < INFINITY)
			return (TRUE);
	}
	return (FALSE);
}

int			rt_sq(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3 p0;
	double h;

	p0 = objlst->u_obj.sq.p0;
	h = objlst->u_obj.sq.h;
	inter->normal = objlst->u_obj.sq.dir;
	if (rt_pl_square(ray, objlst, inter))
	{
		if (fabs(inter->pos.x - p0.x) > (h / 2)
			|| fabs(inter->pos.y - p0.y) > (h / 2)
			|| fabs(inter->pos.z - p0.z) > (h / 2))
			return (FALSE);
		else
			return (TRUE);
	}
	return (FALSE);
}
