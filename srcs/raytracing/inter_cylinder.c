/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 19:53:04 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/30 16:21:01 by julnolle         ###   ########.fr       */
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

int	truncate_cylinder(t_trunc *trunc, t_cy cy, t_vec3 ray, t_vec3 origin)
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

/*enum e_bool intersect_cylinder(t_primitive cp, t_ray r, double *current_z)
{
    t_vec3  pdp = vec3_substract(cp.direction, cp.position);
    t_vec3  eyexpdp = vec3_cross(vec3_substract(r.origin, cp.position), pdp);
    t_vec3  rdxpdp = vec3_cross(r.direction, pdp);
    float   a = vec3_dot(rdxpdp, rdxpdp);
    float   b = 2 * vec3_dot(rdxpdp, eyexpdp);
    float   c = vec3_dot(eyexpdp, eyexpdp) - (cp.radius * cp.radius * vec3_dot(pdp, pdp));
    double  t[2];
    double delta;
    delta = sqrt((b * b) - (4.0 * a * c));
    if (delta < 0)
        return (false);
    t[0] = (-b - (delta)) / (2.0 * a);
    t[1] = (-b + (delta)) / (2.0 * a);
    return (test_intersect(t, current_z));
}
*/
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
