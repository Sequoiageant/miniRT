/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 18:28:19 by julien            #+#    #+#             */
/*   Updated: 2020/03/27 18:16:47 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

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
		r = ft_sub_vec3(inter->pos, p0);
		n = ft_norm_vec3(&r);
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

	tmp = ft_sub_vec3(*ray, ft_multby_vec3(&dir, ft_dot_product3(dir, *ray)));
	tmp2 = ft_sub_vec3(origin, pos);
	tmp3 = ft_sub_vec3(tmp2, ft_multby_vec3(&dir, ft_dot_product3(tmp2, dir)));
	abc.x = ft_dot_product3(tmp, tmp);
	abc.y = 2 * ft_dot_product3(tmp, tmp3);
	abc.z = ft_dot_product3(tmp3, tmp3) - radius * radius;
	if ((delta.x = abc.y * abc.y - 4 * abc.x * abc.z) < 0)
		return (FALSE);
	delta.y = (-abc.y - sqrt(delta.x)) / (2 * abc.x);
	delta.z = (-abc.y + sqrt(delta.x)) / (2 * abc.x);
	tmp = ft_add_vec3(origin, ft_multby_vec3(ray, delta.y));
	origin = ft_add_vec3(origin, ft_multby_vec3(ray, delta.z));
	if (delta.y > EPSILON && ft_dot_product3(dir, ft_sub_vec3(tmp, pos)) > 0 &&
		ft_dot_product3(ft_multby_vec3(&dir, -1.0), ft_sub_vec3(tmp, pos2)) > 0)
	{
		inter->t = delta.y;
		inter->pos = ft_add_vec3(origin, ft_multby_vec3(ray, inter->t));
		dir = ft_sub_vec3(inter->pos, objlst->u_obj.cy.pos);
		theta = sqrt(ft_norm_vec3_2(&dir) - (radius * radius));
		pos = ft_add_vec3(objlst->u_obj.cy.pos,ft_multby_vec3(&objlst->u_obj.cy.dir, theta));
		inter->normal = ft_sub_vec3(inter->pos, pos);
		ft_normalize(&inter->normal);
		return (TRUE);
	}
	if (delta.z > EPSILON && ft_dot_product3(dir, ft_sub_vec3(origin, pos)) > 0 &&
		ft_dot_product3(ft_multby_vec3(&dir, -1.0), ft_sub_vec3(origin, pos2)) > 0)
	{
		inter->t = delta.z;
		inter->pos = ft_add_vec3(origin, ft_multby_vec3(ray, inter->t));
		dir = ft_sub_vec3(inter->pos, objlst->u_obj.cy.pos);
		theta = sqrt(ft_norm_vec3_2(&dir) - (radius * radius));
		pos = ft_add_vec3(objlst->u_obj.cy.pos,ft_multby_vec3(&objlst->u_obj.cy.dir, theta));
		inter->normal = ft_sub_vec3(inter->pos, pos);

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

	pmax = ft_add_vec3(cy.pos,ft_multby_vec3(&cy.dir, cy.h));
	dc = ft_dot_product3(cy.dir, ray);
	dw = ft_dot_product3(ft_sub_vec3(origin, pmax), cy.dir);
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
	oc = ft_sub_vec3(origin, objlst->u_obj.cy.pos);
	w = ft_cross_product3(ray, &objlst->u_obj.cy.dir);
	w2 = ft_norm_vec3_2(&w);

	if (w2 == 0.0)
	{
		a = ft_dot_product3(oc, objlst->u_obj.cy.dir);
		d = ft_sub_vec3(oc, ft_multby_vec3(&objlst->u_obj.cy.dir, a));
		d2 = ft_norm_vec3_2(&d);
		if (d2 > (r * r))
			return (FALSE);
		else
			inter->t = INFINITY;
	}
	else
	{
		w = ft_get_normalized(w);
		gr = fabs(ft_dot_product3(oc, w));
		if (gr > r)
			return (FALSE);
		else
		{
			e = ft_cross_product3(&oc, &objlst->u_obj.cy.dir);
			t = -ft_dot_product3(e, w);
			f = ft_get_normalized(ft_cross_product3(&w, &objlst->u_obj.cy.dir));
			s = sqrt((r * r) - (gr * gr)) / fabs(ft_dot_product3(*ray, f));
			trunc.tin = t - s;
			trunc.tout = t + s;
			if (truncate_cylinder(&trunc, objlst->u_obj.cy, *ray, origin))
			{
				inter->t = trunc.t;
				inter->pos = ft_add_vec3(origin, ft_multby_vec3(ray, inter->t));
				proj = ft_sub_vec3(inter->pos, objlst->u_obj.cy.pos);
			// a = ft_dot_product3(proj, objlst->u_obj.cy.dir);
			// proj = ft_sub_vec3(proj,ft_multby_vec3(&objlst->u_obj.cy.dir, a));
			// inter->normal = ft_divby_vec3(&proj, r);
				theta = acos(ft_dot_product3(proj, w)/(ft_norm_vec3(&proj) * ft_norm_vec3(&w)));
				a = r / tan(theta);
				proj = ft_add_vec3(objlst->u_obj.cy.pos,ft_multby_vec3(&objlst->u_obj.cy.dir, a));
				inter->normal = ft_sub_vec3(inter->pos, proj);
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
