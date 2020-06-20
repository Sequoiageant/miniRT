/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:37:44 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 18:18:47 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		swap_doubles(double *a, double *b)
{
	double buffer;

	buffer = *a;
	*a = *b;
	*b = buffer;
}

static int		solve_quadratic(t_quadra *q)
{
	double nom;

	q->delta = q->b * q->b - 4.0 * q->a * q->c;
	if (q->delta < 0)
		return (FALSE);
	else if (q->delta == 0)
	{
		q->t1 = -0.5 * q->b / q->a;
		q->t2 = -0.5 * q->b / q->a;
	}
	else
	{
		if (q->b > 0)
			nom = -1 * (q->b + sqrt(q->delta)) / 2;
		else
			nom = -1 * (q->b - sqrt(q->delta)) / 2;
		q->t1 = nom / q->a;
		q->t2 = q->c / nom;
	}
	if (q->t1 > q->t2)
		swap_doubles(&q->t1, &q->t2);
	return (TRUE);
}

static t_vec3	get_cylinder_normal(t_inter *inter, t_cy cy)
{
	t_vec3 op;
	t_vec3 normal;

	op = sub_vec3(inter->pos, cy.pos);
	normal = sub_vec3(op, multby_vec3(&cy.dir, dot_product3(cy.dir, op)));
	ft_normalize(&normal);
	return (normal);
}

static void		trunc_cylinder(double *t, t_cy cy, t_vec3 *ray, t_inter *inter)
{
	t_vec3 q;
	t_vec3 p2;

	p2 = add_vec3(cy.pos, multby_vec3(&cy.dir, cy.h));
	q = add_vec3(inter->origin, multby_vec3(ray, *t));
	if (dot_product3(cy.dir, sub_vec3(q, cy.pos)) <= 0.0)
		*t = -1.0;
	if (dot_product3(cy.dir, sub_vec3(q, p2)) >= 0.0)
		*t = -1.0;
}

static int		get_cy_inter(t_quadra *q, t_cy cy, t_vec3 *ray, t_inter *inter)
{
	t_vec3	a_sqrt;
	t_vec3	right;

	a_sqrt = sub_vec3(*ray, multby_vec3(&cy.dir, dot_product3(*ray, cy.dir)));
	q->a = dot_product3(a_sqrt, a_sqrt);
	right = sub_vec3(sub_vec3(inter->origin, cy.pos), multby_vec3(&cy.dir,
		dot_product3(sub_vec3(inter->origin, cy.pos), cy.dir)));
	q->b = 2.0 * dot_product3(a_sqrt, right);
	q->c = dot_product3(right, right) - ((cy.dia * cy.dia) / 4.0);
	if (!solve_quadratic(q))
		return (FALSE);
	return (TRUE);
}

int				rt_cy(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_quadra	q;

	if (get_cy_inter(&q, objlst->u_obj.cy, ray, inter) == FALSE)
		return (FALSE);
	if (q.t1 > 0.0)
		trunc_cylinder(&q.t1, objlst->u_obj.cy, ray, inter);
	if (q.t2 > 0.0)
		trunc_cylinder(&q.t2, objlst->u_obj.cy, ray, inter);
	if (q.t1 < 0.0 && q.t2 < 0.0)
		return (FALSE);
	if (q.t2 < q.t1)
		if (q.t2 > 0)
			inter->t = q.t2;
		else
			inter->t = q.t1;
	else
	{
		if (q.t1 > 0)
			inter->t = q.t1;
		else
			inter->t = q.t2;
	}
	inter->pos = add_vec3(inter->origin, multby_vec3(ray, inter->t));
	inter->normal = get_cylinder_normal(inter, objlst->u_obj.cy);
	return (TRUE);

}
