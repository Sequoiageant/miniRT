/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 18:28:19 by julien            #+#    #+#             */
/*   Updated: 2020/05/03 19:55:13 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		rt_pl_square(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3		origin;
	t_vec3		p0;
	double		denom;

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

int				rt_sq(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3 p2;
	t_vec3 p4;
	t_vec3 e1;
	t_vec3 e2;
	double proj1;
	double proj2;
	t_vec3 v;
	t_vec3 p0;
	double h;

	p0 = objlst->u_obj.sq.p0;
	h = objlst->u_obj.sq.h;
	p2.x = p0.x - h; p2.y = p0.y; p2.z = p0.z;
	p4.x = p0.x; p4.y = p0.y - h; p4.z = p0.z;
	inter->normal = objlst->u_obj.sq.dir;
	// inter->normal = objlst->u_obj.sq.dir;
	if (rt_pl_square(ray, objlst, inter))
	{
		v = sub_vec3(inter->pos, p0);
		e1 = sub_vec3(p0, p2);
		e2 = sub_vec3(p0, p4);
		proj1 = dot_product3(v, e1)/h;
		proj2 = dot_product3(v, e2)/h;
		if((proj1 < h && proj1 > 0.0) && (proj2 < h && proj2 > 0.0))
			return (TRUE);
	}

	return (FALSE);
}

/*int		rt_sq(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3 p1;
	t_vec3 p3;
	t_vec3 nz;
	t_vec3 p0;
	static double teta;
	double h;
	double fov; 
	double length;

	fov = deg_to_rad(60.0);
	p0 = objlst->u_obj.sq.p0;
	h = objlst->u_obj.sq.h;
	length = 2 * fabs(p0.z) * tan(fov/2);
	// printf("%f\n", length);
	nz.x = 0.0; nz.y = 0.0; nz.z = 1.0;
	p1.x = p0.x - length/4; p1.y = p0.y - length/4; p1.z = p0.z;
	p3.x = p0.x + length/4; p3.y = p0.y + length/4; p3.z = p0.z;

	if (rt_pl(ray, objlst, inter))
	{
		if (teta == 0.0)
		{
			teta = acos(dot_product3(inter->normal, nz) / (norm_vec3(&inter->normal) * norm_vec3(&nz)));
			teta = rad_to_deg(teta);
		}
		rot_3d(&p1, teta);
		rot_3d(&p3, teta);
		if (inter->pos.x >= p1.x && inter->pos.x <= p3.x
			&& inter->pos.y >= p1.y && inter->pos.y <= p3.y)
			return (TRUE);
	}

	return (FALSE);
}*/
