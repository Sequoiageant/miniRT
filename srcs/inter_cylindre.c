/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylindre.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 18:28:19 by julien            #+#    #+#             */
/*   Updated: 2020/03/23 19:08:10 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

static int		rt_di(t_vec3 *ray, t_obj *objlst, t_inter *inter)
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
}

int				rt_cy(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	if (rt_di(ray, objlst, inter))	
		return (TRUE);
	return (FALSE);
}
