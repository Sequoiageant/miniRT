/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:02:17 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/22 13:07:58 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rt_sp(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3		origin;
	t_vec3		oc;
	t_quadra	q;
	double		r;

	r = objlst->u_obj.sp.dia / 2;
	origin = inter->origin;
	oc = sub_vec3(origin, objlst->u_obj.sp.pos);
	q.a = norm_vec3_2(ray);
	q.b = 2.0 * dot_product3(*ray, oc);
	q.c = norm_vec3_2(&oc) - (r * r);
	q.delta = q.b * q.b - 4.0 * q.a * q.c;
	if (q.delta < 0.)
		return (FALSE);
	q.t1 = (-q.b - sqrt(q.delta)) / (2 * q.a);
	q.t2 = (-q.b + sqrt(q.delta)) / (2 * q.a);
	if (q.t2 < 0.)
		return (FALSE);
	inter->t = ft_min(q.t1, q.t2);
	inter->pos = add_vec3(origin, multby_vec3(ray, inter->t));
	inter->normal = sub_vec3(inter->pos, objlst->u_obj.sp.pos);
	ft_normalize(&inter->normal);
	return (TRUE);
}
