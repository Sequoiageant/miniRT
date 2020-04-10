/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:50:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/10 16:49:37 by julnolle         ###   ########.fr       */
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

int	set_sp(char **tab, t_obj **objlst, t_data *data, t_stm *machine)
{
	t_sp	sp;
	int		ret;

	ret = SUCCESS;
	ret = set_vector(tab[1], &sp.pos, &machine->error);
	sp.dia = ft_atof(tab[2]);
	if (sp.dia < 0.0)
	{
		machine->error |= SIGN_ERROR_MASK;
		ret = FAILURE;
	}
	if (ret != FAILURE)
	{
		ret = set_color(tab[3], &sp.color, &machine->error);
		ft_add_sp(objlst, sp, data);
		machine->objlst_set = TRUE;
	}
	// print_list2((*objlst));
	return (ret);
}

int	set_sq(char **tab, t_obj **objlst, t_data *data, t_stm *machine)
{
	t_sq	sq;
	int		ret;

	ret = SUCCESS;
	ret = set_vector(tab[1], &sq.p0, &machine->error);
	if (ret != FAILURE)
		ret = set_normal_vec(tab[2], &sq.dir, &machine->error);
	if (is_int_or_float(tab[3], '+'))
		sq.h = ft_atof(tab[3]);
	else
	{
		machine->error |= SIGN_ERROR_MASK;
		ret = FAILURE;
	}
	if (ret != FAILURE)
	{
		ret = set_color(tab[4], &sq.color, &machine->error);
		ft_add_sq(objlst, sq, data);
		machine->objlst_set = TRUE;
	}
	return (ret);
}

int	set_pl(char **tab, t_obj **objlst, t_data *data, t_stm *machine)
{
	t_pl	pl;
	int		ret;

	ret = set_vector(tab[1], &pl.pos, &machine->error);
	if (ret != FAILURE)
		ret = set_normal_vec(tab[2], &pl.normal, &machine->error);
	if (ret != FAILURE)
	{
		ret = set_color(tab[3], &pl.color, &machine->error);
		ft_add_pl(objlst, pl, data);
		machine->objlst_set = TRUE;
	}
	return (ret);
}

int	set_cy(char **tab, t_obj **objlst, t_data *data, t_stm *machine)
{
	t_cy	cy;
	int		ret;

	ret = set_vector(tab[1], &cy.pos, &machine->error);
	if (ret != FAILURE)
		ret = set_normal_vec(tab[2], &cy.dir, &machine->error);
	if (is_int_or_float(tab[3], '+') && is_int_or_float(tab[4], '+'))
	{
		cy.dia = ft_atof(tab[3]);
		cy.h = ft_atof(tab[4]);
	}
	else
	{
		machine->error |= SIGN_ERROR_MASK;
		ret = FAILURE;
	}
	if (ret != FAILURE)
	{
		ret = set_color(tab[5], &cy.color, &machine->error);
		ft_add_cy(objlst, cy, data);
		machine->objlst_set = TRUE;
	}
	return (ret);
}

int	set_tr(char **tab, t_obj **objlst, t_data *data, t_stm *machine)
{
	t_tr	tr;
	int		ret;

	ret = SUCCESS;
	ret = set_vector(tab[1], &tr.p1, &machine->error);
	if (ret != FAILURE)
		ret = set_vector(tab[2], &tr.p2, &machine->error);
	if (ret != FAILURE)
		ret = set_vector(tab[3], &tr.p3, &machine->error);
	if (ret != FAILURE)
	{
		ret = set_color(tab[4], &tr.color, &machine->error);
		ft_add_tr(objlst, tr, data);
		machine->objlst_set = TRUE;
	}
	return (ret);
}
