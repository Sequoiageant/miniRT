/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:50:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/07 16:29:34 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*void	print_list2(t_obj *objlst)
{
	t_sp	*sp;

	while (objlst)
	{
		if (objlst->type == SPHERE)
		{
			sp = (objlst->content);
			printf("	-->%f\n", sp->dia);
		}
		objlst = objlst->next;
	}
}
*/
/*void	ft_add_obj(t_obj **objlst, void *content, int type, t_data *data)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->type = type;
		new->content = content;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);
	if (type == SPHERE)
		printf("<%f>\n", ((t_sp *)data->objlst->content)->dia);
	ft_putendl("	-->element added");
}*/

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

	ft_putendl("	-->element added");
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

	ft_putendl("	-->element added");
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

	ft_putendl("	-->element added");
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

	ft_putendl("	-->element added");
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

	ft_putendl("	-->element added");
}

int	set_sp(char **tab, t_obj **objlst, t_data *data, int *err)
{
	t_sp	sp;
	int		ret;

	ret = SUCCESS;
	ret = set_vector(tab[1], &sp.pos, err);
	sp.dia = ft_atof(tab[2]);
	if (sp.dia < 0.0)
	{
		*err |= SIGN_ERROR_MASK;
		ret = FAILURE;
	}
	if (ret != FAILURE)
	{
		ret = set_color(tab[3], &sp.color, err);
		ft_add_sp(objlst, sp, data);
	}
	// print_list2((*objlst));
	return (ret);
}

int	set_sq(char **tab, t_obj **objlst, t_data *data, int *err)
{
	t_sq	sq;
	int		ret;

	ret = SUCCESS;
	ret = set_vector(tab[1], &sq.p0, err);
	if (ret != FAILURE)
		ret = set_normal_vec(tab[2], &sq.dir, err);
	if (is_int_or_float(tab[3], '+'))
		sq.h = ft_atof(tab[3]);
	else
	{
		*err |= SIGN_ERROR_MASK;
		ret = FAILURE;
	}
	if (ret != FAILURE)
	{
		ret = set_color(tab[4], &sq.color, err);
		ft_add_sq(objlst, sq, data);
	}
	return (ret);
}

int	set_pl(char **tab, t_obj **objlst, t_data *data, int *err)
{
	t_pl	pl;
	int		ret;

	ret = set_vector(tab[1], &pl.pos, err);
	if (ret != FAILURE)
		ret = set_normal_vec(tab[2], &pl.normal, err);
	if (ret != FAILURE)
	{
		ret = set_color(tab[3], &pl.color, err);
		ft_add_pl(objlst, pl, data);
	}
	return (ret);
}

int	set_cy(char **tab, t_obj **objlst, t_data *data, int *err)
{
	t_cy	cy;
	int ret;

	ret = set_vector(tab[1], &cy.pos, err);
	if (ret != FAILURE)
		ret = set_normal_vec(tab[2], &cy.dir, err);
	if (is_int_or_float(tab[3], '+') && is_int_or_float(tab[4], '+'))
	{
		cy.dia = ft_atof(tab[3]);
		cy.h = ft_atof(tab[4]);
	}
	else
	{
		*err |= SIGN_ERROR_MASK;
		ret = FAILURE;
	}
	if (ret != FAILURE)
	{
		ret = set_color(tab[5], &cy.color, err);
		ft_add_cy(objlst, cy, data);
	}
	return (ret);
}

int	set_tr(char **tab, t_obj **objlst, t_data *data, int *err)
{
	t_tr	tr;
	int		ret;

	ret = SUCCESS;
	ret = set_vector(tab[1], &tr.p1, err);
	if (ret != FAILURE)
		ret = set_vector(tab[2], &tr.p2, err);
	if (ret != FAILURE)
		ret = set_vector(tab[3], &tr.p3, err);
	if (ret != FAILURE)
	{
		ret = set_color(tab[4], &tr.color, err);
		ft_add_tr(objlst, tr, data);
	}
	return (ret);
}
