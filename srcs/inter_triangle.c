/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 18:28:19 by julien            #+#    #+#             */
/*   Updated: 2020/03/25 12:18:37 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

static int		rt_pl_triangle(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3		origin;
	t_vec3		p3;
	double		denom;

	p3 = objlst->u_obj.tr.p3;
	origin = inter->origin;
	denom = ft_dot_product3(*ray, inter->normal);
	if (fabs(denom) > EPSILON)
	{	
		inter->t = (ft_dot_product3(ft_sub_vec3(p3, origin), inter->normal)) / denom; 
		inter->pos = ft_add_vec3(origin, ft_multby_vec3(ray, inter->t));
		if (inter->t >= 0.0 && inter->t < INFINITY)
			return (TRUE);
	} 
	return (FALSE);
}


int				rt_tr(t_vec3 *ray, t_obj *objlst, t_inter *inter)
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
	u = ft_sub_vec3(tr.p3, tr.p1);
	v = ft_sub_vec3(tr.p2, tr.p1);
	inter->normal = ft_cross_product3(&u, &v);

	if (rt_pl_triangle(ray, objlst, inter))
	{
		w = ft_sub_vec3(inter->pos, tr.p1);
		m11 = ft_norm_vec3_2(&u);
		m12 = ft_dot_product3(u, v);
		m22 = ft_norm_vec3_2(&v);
		detm = m11 * m22 - m12 * m12;

		b11 = ft_dot_product3(w, u);
		b21 = ft_dot_product3(w, v);
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
	denom = ft_dot_product3(*ray, inter->normal);
	if (fabs(denom) > EPSILON)
	{	
		inter->t = (ft_dot_product3(ft_sub_vec3(p3, origin), inter->normal)) / denom; 
		inter->pos = ft_add_vec3(origin, ft_multby_vec3(ray, inter->t));
		if (inter->t >= 0.0 && inter->t < INFINITY)
			return (TRUE);
	} 
	return (FALSE);
}

int		rt_tr(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_tr tr;
	t_vec3 p1p2;
	t_vec3 p1p3;
	t_vec3 p2p3;
	t_vec3 c1;
	t_vec3 c2;
	t_vec3 c3;

	tr = objlst->u_obj.tr;
	p1p2 = ft_sub_vec3(tr.p1, tr.p2);
	p1p3 = ft_sub_vec3(tr.p1, tr.p3);
	p2p3 = ft_sub_vec3(tr.p2, tr.p3);
	inter->normal = ft_get_normalized(ft_cross_product3(&p1p2, &p1p3));
	// printf("%f\n", d);
	if (rt_pl_triangle(ray, inter, tr.p3))
	{
		c1 = ft_sub_vec3(inter->pos, tr.p1);
		c2 = ft_sub_vec3(inter->pos, tr.p2);
		c3 = ft_sub_vec3(inter->pos, tr.p3);
		if (ft_dot_product3(inter->normal, ft_cross_product3(&p1p2, &c1)) > 0.0
			&& ft_dot_product3(inter->normal, ft_cross_product3(&p1p3, &c2)) > 0.0
			&& ft_dot_product3(inter->normal, ft_cross_product3(&p2p3, &c3)) > 0.0)
			return (TRUE);
	}
	return (FALSE);
}
*/