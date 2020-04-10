/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:05:38 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/10 19:05:55 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_add_sp(t_obj **objlst, t_sp sp, t_data *data)
{
	t_obj *new;

	new = (t_obj*)malloc(sizeof(t_obj));
	if (new)
	{
		new->type = SPHERE;
		new->col = sp.color;
		new->u_obj.sp = sp;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);
	data->objlst_set = TRUE;
}

void	ft_add_sq(t_obj **objlst, t_sq sq, t_data *data)
{
	t_obj *new;

	new = (t_obj*)malloc(sizeof(t_obj));
	if (new)
	{
		new->type = SQUARE;
		new->col = sq.color;
		new->u_obj.sq = sq;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);
	data->objlst_set = TRUE;
}

void	ft_add_pl(t_obj **objlst, t_pl pl, t_data *data)
{
	t_obj *new;

	new = (t_obj*)malloc(sizeof(t_obj));
	if (new)
	{
		new->type = PLANE;
		new->col = pl.color;
		new->u_obj.pl = pl;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);
	data->objlst_set = TRUE;
}

void	ft_add_cy(t_obj **objlst, t_cy cy, t_data *data)
{
	t_obj *new;

	new = (t_obj*)malloc(sizeof(t_obj));
	if (new)
	{
		new->type = CYLINDER;
		new->col = cy.color;
		new->u_obj.cy = cy;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);
	data->objlst_set = TRUE;
}

void	ft_add_tr(t_obj **objlst, t_tr tr, t_data *data)
{
	t_obj *new;

	new = (t_obj*)malloc(sizeof(t_obj));
	if (new)
	{
		new->type = TRIANGLE;
		new->col = tr.color;
		new->u_obj.tr = tr;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);
	data->objlst_set = TRUE;
}
