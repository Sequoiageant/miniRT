/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 18:28:19 by julien            #+#    #+#             */
/*   Updated: 2020/06/18 18:35:56 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_pl_triangle(t_vec3 *ray, t_tr tr, t_inter *inter)
{
	t_vec3		origin;
	double		denom;

	origin = inter->origin;
	denom = dot_product3(*ray, inter->normal);
	if (fabs(denom) > EPSILON)
	{
		inter->t = (dot_product3(sub_vec3(tr.p1, origin), inter->normal)) / denom; 
		inter->pos = add_vec3(origin, multby_vec3(ray, inter->t));
		if (inter->t >= 0.0 && inter->t < INFINITY)
			return (TRUE);
	}
	return (FALSE);
}

/*int			check_edges(t_tr tr, t_inter *inter)
{
	t_vec3	c;
	t_vec3	edge;
	t_vec3	w;

	edge = sub_vec3(tr.p2, tr.p1);
	w = sub_vec3(inter->pos, tr.p1);
	c = cross_product3(&edge, &w);
	if (dot_product3(inter->normal, c) < 0)
		return (FALSE);
	edge = sub_vec3(tr.p3, tr.p2);
	w = sub_vec3(inter->pos, tr.p2);
	c = cross_product3(&edge, &w);
	if (dot_product3(inter->normal, c) < 0)
		return (FALSE);
	edge = sub_vec3(tr.p1, tr.p3);
	w = sub_vec3(inter->pos, tr.p3);
	c = cross_product3(&edge, &w);
	if (dot_product3(inter->normal, c) < 0)
		return (FALSE);
	return (TRUE);
}


int			rt_tr(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_tr tr;
	t_vec3 u;
	t_vec3 v;

	tr = objlst->u_obj.tr;
	u = sub_vec3(tr.p2, tr.p1);
	v = sub_vec3(tr.p3, tr.p1);
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
}*/

int			rt_tr(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_tr tr;
	t_vec3 u;
	t_vec3 v;
	t_vec3 w;
	double m11;
	double m12;
	double m22;
	double detm;
	double b11;
	double b21;
	double detb;
	double beta;
	double g12;
	double g22;
	double detg;
	double gamma;
	double alpha;

	tr = objlst->u_obj.tr;
	u = sub_vec3(tr.p3, tr.p1);
	v = sub_vec3(tr.p2, tr.p1);
	inter->normal = cross_product3(&u, &v);

	if (rt_pl_triangle(ray, tr, inter))
	{
		w = sub_vec3(inter->pos, tr.p1);
		m11 = norm_vec3_2(&u);
		m12 = dot_product3(u, v);
		m22 = norm_vec3_2(&v);
		detm = m11 * m22 - m12 * m12;

		b11 = dot_product3(w, u);
		b21 = dot_product3(w, v);
		detb = b11 * m22 - b21 * m12;
		beta = detb / detm;

		g12 = b11;
		g22 = b21;
		detg = m11 * g22 - m12 * g12;
		gamma = detg / detm;

		alpha = 1 - beta - gamma;
		if (alpha < EPSILON || alpha > 1.0)
			return (FALSE);
		if (beta < EPSILON || beta > 1.0)
			return (FALSE);
		if (gamma < EPSILON || gamma > 1.0)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

/*int		rt_pl_triangle(t_vec3 *ray, t_inter *inter, t_vec3 p3)
{
	t_vec3		origin;
	double		denom;

	origin = inter->origin;
	denom = dot_product3(*ray, inter->normal);
	if (fabs(denom) > EPSILON)
	{	
		inter->t = (dot_product3(sub_vec3(p3, origin), inter->normal)) / denom; 
		inter->pos = add_vec3(origin, multby_vec3(ray, inter->t));
		if (inter->t >= 0.0 && inter->t < INFINITY)
			return (TRUE);
	} 
	return (FALSE);
}
*/

/*int		rt_tr(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_tr tr;
	t_vec3 a;
	t_vec3 b;
	t_vec3 c;
	t_vec3 c1;
	t_vec3 c2;
	t_vec3 c3;

	tr = objlst->u_obj.tr;
	a = sub_vec3(tr.p1, tr.p2);
	b = sub_vec3(tr.p1, tr.p3);
	c = sub_vec3(tr.p2, tr.p3);
	inter->normal = get_normalized(cross_product3(&b, &a));
	// printf("%f\n", d);
	if (rt_pl_triangle(ray, tr, inter))
	{
		c1 = sub_vec3(inter->pos, tr.p1);
		c2 = sub_vec3(inter->pos, tr.p2);
		c3 = sub_vec3(inter->pos, tr.p3);
		if (dot_product3(inter->normal, cross_product3(&a, &c1)) > 0.0
			&& dot_product3(inter->normal, cross_product3(&b, &c2)) > 0.0
			&& dot_product3(inter->normal, cross_product3(&c, &c3)) > 0.0)
			return (TRUE);
	}
	return (FALSE);
}*/