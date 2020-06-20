/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:14:45 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 16:18:45 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_pl_triangle(t_vec3 *ray, t_tr tr, t_inter *inter)
{
	t_vec3		origin;
	double		nom;
	double		denom;

	origin = inter->origin;
	denom = dot_product3(*ray, inter->normal);
	if (fabs(denom) > EPSILON)
	{
		nom = dot_product3(sub_vec3(tr.p1, origin), inter->normal);
		inter->t = nom / denom;
		inter->pos = add_vec3(origin, multby_vec3(ray, inter->t));
		if (inter->t >= 0.0 && inter->t < INFINITY)
			return (TRUE);
	}
	return (FALSE);
}

static int	check_edges(t_tr tr, t_inter *inter)
{
	t_vec3	c;
	t_vec3	edge;
	t_vec3	w;

	edge = sub_vec3(tr.p1, tr.p2);
	w = sub_vec3(inter->pos, tr.p1);
	c = cross_product3(&edge, &w);
	if (dot_product3(inter->normal, c) < 0)
		return (FALSE);
	edge = sub_vec3(tr.p2, tr.p3);
	w = sub_vec3(inter->pos, tr.p2);
	c = cross_product3(&edge, &w);
	if (dot_product3(inter->normal, c) < 0)
		return (FALSE);
	edge = sub_vec3(tr.p3, tr.p1);
	w = sub_vec3(inter->pos, tr.p3);
	c = cross_product3(&edge, &w);
	if (dot_product3(inter->normal, c) < 0)
		return (FALSE);
	return (TRUE);
}

int			rt_tr(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_tr	tr;
	t_vec3	u;
	t_vec3	v;

	tr = objlst->u_obj.tr;
	u = sub_vec3(tr.p3, tr.p1);
	v = sub_vec3(tr.p2, tr.p1);
	inter->normal = cross_product3(&u, &v);
	ft_normalize(&inter->normal);
	if (rt_pl_triangle(ray, tr, inter))
	{
		if (check_edges(tr, inter) == FALSE)
			return (FALSE);
		else
			return (TRUE);
	}
	return (FALSE);
}
