/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:37:44 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/19 15:51:18 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*static int		rt_di(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3 p0;
	t_vec3 r;
	double n;
	double dia;

	p0 = objlst->u_obj.cy.pos;
	dia = objlst->u_obj.cy.dia;
	if (rt_pl(ray, objlst, inter))
	{
		r = sub_vec3(inter->pos, p0);
		n = norm_vec3(&r);
		if(n < dia/2)
			return (TRUE);
	}
	return (FALSE);
}*/

/*int				rt_cy(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3 tmp;
	t_vec3 tmp2;
	t_vec3 tmp3;
	t_vec3 abc;
	t_vec3 delta;
	t_vec3 dir;
	t_vec3 origin;
	t_vec3 pos;
	t_vec3 pos2;
	double radius;
	double theta;
	t_vec3 nz;
	nz.x = 0.0;
	nz.y = 0.0;
	nz.z = -1.0;

	dir = objlst->u_obj.cy.dir;
	origin = inter->origin;
	radius = objlst->u_obj.cy.dia / 2;
	pos = objlst->u_obj.cy.pos;
	pos2.x = objlst->u_obj.cy.pos.x;
	pos2.y = objlst->u_obj.cy.pos.y - objlst->u_obj.cy.h;
	pos2.z = objlst->u_obj.cy.pos.z;

	tmp = sub_vec3(*ray, multby_vec3(&dir, dot_product3(dir, *ray)));
	tmp2 = sub_vec3(origin, pos);
	tmp3 = sub_vec3(tmp2, multby_vec3(&dir, dot_product3(tmp2, dir)));
	abc.x = dot_product3(tmp, tmp);
	abc.y = 2 * dot_product3(tmp, tmp3);
	abc.z = dot_product3(tmp3, tmp3) - radius * radius;
	if ((delta.x = abc.y * abc.y - 4 * abc.x * abc.z) < 0)
		return (FALSE);
	delta.y = (-abc.y - sqrt(delta.x)) / (2 * abc.x);
	delta.z = (-abc.y + sqrt(delta.x)) / (2 * abc.x);
	tmp = add_vec3(origin, multby_vec3(ray, delta.y));
	origin = add_vec3(origin, multby_vec3(ray, delta.z));
	if (delta.y > EPSILON && dot_product3(dir, sub_vec3(tmp, pos)) > 0 &&
		dot_product3(multby_vec3(&dir, -1.0), sub_vec3(tmp, pos2)) > 0)
	{
		inter->t = delta.y;
		inter->pos = add_vec3(origin, multby_vec3(ray, inter->t));
		dir = sub_vec3(inter->pos, objlst->u_obj.cy.pos);
		theta = sqrt(norm_vec3_2(&dir) - (radius * radius));
		pos = add_vec3(objlst->u_obj.cy.pos,multby_vec3(&objlst->u_obj.cy.dir, theta));
		inter->normal = sub_vec3(inter->pos, pos);
		ft_normalize(&inter->normal);
		return (TRUE);
	}
	if (delta.z > EPSILON && dot_product3(dir, sub_vec3(origin, pos)) > 0 &&
		dot_product3(multby_vec3(&dir, -1.0), sub_vec3(origin, pos2)) > 0)
	{
		inter->t = delta.z;
		inter->pos = add_vec3(origin, multby_vec3(ray, inter->t));
		dir = sub_vec3(inter->pos, objlst->u_obj.cy.pos);
		theta = sqrt(norm_vec3_2(&dir) - (radius * radius));
		pos = add_vec3(objlst->u_obj.cy.pos,multby_vec3(&objlst->u_obj.cy.dir, theta));
		inter->normal = sub_vec3(inter->pos, pos);

		ft_normalize(&inter->normal);
		return (TRUE);
	}
	return (FALSE);
}*/

/*int				rt_cy(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3 origin;
	t_vec3 oc;
	double uz = ray->z * ray->z;


	origin = inter->origin;
	r = objlst->u_obj.cy.dia / 2;

			return (TRUE);
	return (FALSE);
}*/
void		swap_doubles(double *a, double *b)
{
	double buffer;

	buffer = *a;
	*a = *b;
	*b = buffer;
}
int			solve_quadratic(t_quadra *q)
{
	double delta;
	double det;

	delta = pow(q->b, 2) - 4.0 * q->a * q->c;
	if (delta < 0)
		return (FALSE);
	else if (delta == 0)
	{
		q->t1 = -0.5 * q->b / q->a;
		q->t2 = -0.5 * q->b / q->a;
	}
	else
	{
		if (q->b > 0)
			det = -1 * (q->b + sqrt(delta)) / 2;
		else
			det = -1 * (q->b - sqrt(delta)) / 2;
		q->t1 = det / q->a;
		q->t2 = q->c / det;
	}
	if (q->t1 > q->t2)
		swap_doubles(&q->t1, &q->t2);
	return (TRUE);
}

t_vec3		get_cylinder_normal(t_inter *inter, t_cy cy)
{
	t_vec3 ctp;
	t_vec3 normal;

	ctp = sub_vec3(inter->pos, cy.pos);
	normal = sub_vec3(ctp, multby_vec3(&cy.dir, dot_product3(cy.dir, ctp)));
	ft_normalize(&normal);
	return (normal);
}

void		check_t(double *t, t_cy cy, t_vec3 *ray, t_inter *inter)
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

int			cyl_get_roots(t_quadra *q, t_cy cy,	t_vec3 *ray, t_inter *inter)
{
	t_vec3	a_sqrt;
	t_vec3	right;

	a_sqrt = sub_vec3(*ray, multby_vec3(&cy.dir, dot_product3(*ray, cy.dir)));
	q->a = dot_product3(a_sqrt, a_sqrt);
	right = sub_vec3(sub_vec3(inter->origin, cy.pos), multby_vec3(&cy.dir,
				dot_product3(sub_vec3(inter->origin, cy.pos), cy.dir)));
	q->b = 2.0 * dot_product3(a_sqrt, right);
	q->c = dot_product3(right, right) - ((cy.dia / 2.0) * (cy.dia / 2.0));
	if (!solve_quadratic(q))
		return (FALSE);
	return (TRUE);
}

int				rt_cy(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_quadra	q;

	if (!cyl_get_roots(&q, objlst->u_obj.cy, ray, inter))
		return (FALSE);
	if (q.t1 > 0.0)
		check_t(&q.t1, objlst->u_obj.cy, ray, inter);
	if (q.t2 > 0.0)
		check_t(&q.t2, objlst->u_obj.cy, ray, inter);
	if (q.t1 < 0.0 && q.t2 < 0.0)
		return (FALSE);
	if (q.t2 < q.t1)
		if (q.t2 > 0.0)
			inter->t = q.t2;
		else
			inter->t = q.t1;
	else
	{
		if (q.t1 > 0.0)
			inter->t = q.t1;
		else
			inter->t = q.t2;
	}
	inter->pos = add_vec3(inter->origin, multby_vec3(ray, inter->t));
	inter->normal = get_cylinder_normal(inter, objlst->u_obj.cy);
	return (TRUE);
}



/*BOOOOOOOOOOOOOOOOOONNNNNNNNNNNNN*/
/*int	truncate_cylinder(t_trunc *trunc, t_cy cy, t_vec3 ray, t_vec3 origin)
{
	t_vec3 pmax;
	double dc;
	double dw;

	pmax = add_vec3(cy.pos,multby_vec3(&cy.dir, cy.h));
	dc = dot_product3(cy.dir, ray);
	dw = dot_product3(sub_vec3(origin, pmax), cy.dir);
	if (dc == 0.0)
	{
		if (dw > 0.0)
			return (FALSE);
	}
	else
	{
		trunc->t = -dw / dc;
		if (dc >= 0.0)
		{
			if (trunc->t > trunc->tin && trunc->t < trunc->tout)
				trunc->tout = trunc->t;
			if (trunc->t < trunc->tin)
				return (FALSE);
		}
		else
		{
			if (trunc->t > trunc->tin && trunc->t < trunc->tout)
				trunc->tin = trunc->t;
			if (trunc->t > trunc->tout)
				return (FALSE);
		}
	}
	if (trunc->tin > trunc->tout)
		return (FALSE);
	trunc->t = trunc->tin;
	return (TRUE);
}

int				rt_cy(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3 origin;
	t_vec3 oc;
	t_vec3 w;
	t_vec3 d;
	t_vec3 e;
	t_vec3 f;
	double r;
	double w2;
	double a;
	double d2;
	double gr;
	double s;
	double t;
	double theta;
	t_vec3 proj;
	t_trunc trunc;

	origin = inter->origin;
	r = objlst->u_obj.cy.dia / 2;
	oc = sub_vec3(origin, objlst->u_obj.cy.pos);
	w = cross_product3(ray, &objlst->u_obj.cy.dir);
	w2 = norm_vec3_2(&w);

	if (w2 == 0.0)
	{
		a = dot_product3(oc, objlst->u_obj.cy.dir);
		d = sub_vec3(oc, multby_vec3(&objlst->u_obj.cy.dir, a));
		d2 = norm_vec3_2(&d);
		if (d2 > (r * r))
			return (FALSE);
		else
			inter->t = INFINITY;
	}
	else
	{
		w = get_normalized(w);
		gr = fabs(dot_product3(oc, w));
		if (gr > r)
			return (FALSE);
		else
		{
			e = cross_product3(&oc, &objlst->u_obj.cy.dir);
			t = -dot_product3(e, w);
			f = get_normalized(cross_product3(&w, &objlst->u_obj.cy.dir));
			s = sqrt((r * r) - (gr * gr)) / fabs(dot_product3(*ray, f));
			trunc.tin = t - s;
			trunc.tout = t + s;
			if (truncate_cylinder(&trunc, objlst->u_obj.cy, *ray, origin))
			{
				inter->t = trunc.t;
				inter->pos = add_vec3(origin, multby_vec3(ray, inter->t));
				proj = sub_vec3(inter->pos, objlst->u_obj.cy.pos);
			// a = dot_product3(proj, objlst->u_obj.cy.dir);
			// proj = sub_vec3(proj,multby_vec3(&objlst->u_obj.cy.dir, a));
			// inter->normal = divby_vec3(&proj, r);
				theta = acos(dot_product3(proj, w)/(norm_vec3(&proj) * norm_vec3(&w)));
				a = r / tan(theta);
				proj = add_vec3(objlst->u_obj.cy.pos,multby_vec3(&objlst->u_obj.cy.dir, a));
				inter->normal = sub_vec3(inter->pos, proj);
				ft_normalize(&inter->normal);
				return (TRUE);
			}
			else
				return (FALSE);
		}
		return (FALSE);
	}
	return (FALSE);
}
*/
/*END BOOOOOOOOOOONNNNNNNNNN*/