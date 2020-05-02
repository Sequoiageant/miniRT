/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:03:14 by julien            #+#    #+#             */
/*   Updated: 2020/03/25 16:53:16 by julien           ###   ########.fr       */
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

 /*// Solution normalement optimisée
int		rt_sp(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3		origin;
	t_vec3		oc;
	double		q;
	double		r2;
	double		d;
	double		l;
	double		m;

	origin = inter->origin;
	r2 = (objlst->u_obj.sp.dia * objlst->u_obj.sp.dia) / 4;
	oc = sub_vec3(objlst->u_obj.sp.pos, origin);
	d = dot_product3(*ray, oc);
	l = norm_vec3_2(&oc);

	if (d < 0.0 && l < r2)
		return (FALSE);
	m = l - (d * d);
	if (m > r2)
		return (FALSE);
	q = sqrt(r2 - m);
	if (l > r2)
		inter->t = d - q;
	else
		inter->t = d + q;
	inter->pos = add_vec3(origin, multby_vec3(ray, inter->t));
	inter->normal = sub_vec3(inter->pos, objlst->u_obj.sp.pos);
	ft_normalize(&inter->normal);
	return (TRUE);
}*/
