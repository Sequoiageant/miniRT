/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:50:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/03 19:44:15 by julnolle         ###   ########.fr       */
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
		new->num = num;
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

void	ft_add_sp(t_obj **objlst, t_sp sp, int type, t_data *data, int num)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->num = num;
		new->type = type;
		new->u_obj.sp = sp;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);
	// if (type == SPHERE)
	// 	printf("<%f>\n", ((t_sp *)data->objlst->content)->dia);
	ft_putendl("	-->element added");
}

void	ft_add_sq(t_obj **objlst, t_sq sq, int type, t_data *data, int num)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->num = num;
		new->type = type;
		new->u_obj.sq = sq;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);

	ft_putendl("	-->element added");
}

void	ft_add_pl(t_obj **objlst, t_pl pl, int type, t_data *data, int num)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->num = num;
		new->type = type;
		new->u_obj.pl = pl;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);

	ft_putendl("	-->element added");
}

void	ft_add_cy(t_obj **objlst, t_cy cy, int type, t_data *data, int num)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->num = num;
		new->type = type;
		new->u_obj.cy = cy;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);

	ft_putendl("	-->element added");
}

void	ft_add_tr(t_obj **objlst, t_tr tr, int type, t_data *data, int num)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->num = num;
		new->type = type;
		new->u_obj.tr = tr;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);

	ft_putendl("	-->element added");
}

int	set_sp(char **tab, t_obj **objlst, t_data *data, int num)
{
	t_sp	sp;
	char	**sp_set;

	sp_set = ft_split(tab[1], ',');
	if (sp_set != NULL)
	{
		sp.pos.x = ft_atof(sp_set[0]);
		sp.pos.y = ft_atof(sp_set[1]);
		sp.pos.z = ft_atof(sp_set[2]);
		ft_free_tab2(sp_set);
	}
	sp.dia = ft_atof(tab[2]);
	sp_set = ft_split(tab[3], ',');
	if (sp_set != NULL)
	{
		sp.color.r = ft_atof(sp_set[0]);
		sp.color.g = ft_atof(sp_set[1]);
		sp.color.b = ft_atof(sp_set[2]);
		ft_free_tab2(sp_set);
	}
	ft_add_sp(objlst, sp, SPHERE, data, num);
	// print_list2((*objlst));
	return (0);
}

int	set_sq(char **tab, t_obj **objlst, t_data *data, int num)
{
	t_sq	sq;
	char	**sq_set;

	sq_set = ft_split(tab[1], ',');
	if (sq_set != NULL)
	{
		sq.pos.x = ft_atof(sq_set[0]);
		sq.pos.y = ft_atof(sq_set[1]);
		sq.pos.z = ft_atof(sq_set[2]);
		ft_free_tab2(sq_set);
	}
	sq_set = ft_split(tab[2], ',');
	if (sq_set != NULL)
	{
		sq.dir.x = ft_atof(sq_set[0]);
		sq.dir.y = ft_atof(sq_set[1]);
		sq.dir.z = ft_atof(sq_set[2]);
		ft_free_tab2(sq_set);
	}
	sq.h = ft_atof(tab[3]);
	sq_set = ft_split(tab[4], ',');
	if (sq_set != NULL)
	{
		sq.color.r = ft_atof(sq_set[0]);
		sq.color.g = ft_atof(sq_set[1]);
		sq.color.b = ft_atof(sq_set[2]);
		ft_free_tab2(sq_set);
	}
	ft_add_sq(objlst, sq, SQUARE, data, num);
	return (0);
}

int	set_pl(char **tab, t_obj **objlst, t_data *data, int num)
{
	t_pl	pl;
	char	**pl_set;

	pl_set = ft_split(tab[1], ',');
	if (pl_set != NULL)
	{
		pl.pos.x = ft_atof(pl_set[0]);
		pl.pos.y = ft_atof(pl_set[1]);
		pl.pos.z = ft_atof(pl_set[2]);
		ft_free_tab2(pl_set);
	}
	pl_set = ft_split(tab[2], ',');
	if (pl_set != NULL)
	{
		pl.dir.x = ft_atof(pl_set[0]);
		pl.dir.y = ft_atof(pl_set[1]);
		pl.dir.z = ft_atof(pl_set[2]);
		ft_free_tab2(pl_set);
	}
	pl_set = ft_split(tab[3], ',');
	if (pl_set != NULL)
	{
		pl.color.r = ft_atof(pl_set[0]);
		pl.color.g = ft_atof(pl_set[1]);
		pl.color.b = ft_atof(pl_set[2]);
		ft_free_tab2(pl_set);
	}
	ft_add_pl(objlst, pl, PLANE, data, num);
	return (0);
}

int	set_cy(char **tab, t_obj **objlst, t_data *data, int num)
{
	t_cy	cy;
	char	**cy_set;

	cy_set = ft_split(tab[1], ',');
	if (cy_set != NULL)
	{
		cy.pos.x = ft_atof(cy_set[0]);
		cy.pos.y = ft_atof(cy_set[1]);
		cy.pos.z = ft_atof(cy_set[2]);
		ft_free_tab2(cy_set);
	}
	cy_set = ft_split(tab[2], ',');
	if (cy_set != NULL)
	{
		cy.dir.x = ft_atof(cy_set[0]);
		cy.dir.y = ft_atof(cy_set[1]);
		cy.dir.z = ft_atof(cy_set[2]);
		ft_free_tab2(cy_set);
	}
	cy_set = ft_split(tab[3], ',');
	if (cy_set != NULL)
	{
		cy.color.r = ft_atof(cy_set[0]);
		cy.color.g = ft_atof(cy_set[1]);
		cy.color.b = ft_atof(cy_set[2]);
		ft_free_tab2(cy_set);
	}
	cy.dia = ft_atof(tab[4]);
	cy.h = ft_atof(tab[5]);
	ft_add_cy(objlst, cy, CYLINDER, data, num);
	return (0);
}

int	set_tr(char **tab, t_obj **objlst, t_data *data, int num)
{
	t_tr	tr;
	char	**tr_set;

	tr_set = ft_split(tab[1], ',');
	if (tr_set != NULL)
	{
		tr.pos1.x = ft_atof(tr_set[0]);
		tr.pos1.y = ft_atof(tr_set[1]);
		tr.pos1.z = ft_atof(tr_set[2]);
		ft_free_tab2(tr_set);
	}
	tr_set = ft_split(tab[2], ',');
	if (tr_set != NULL)
	{
		tr.pos2.x = ft_atof(tr_set[0]);
		tr.pos2.y = ft_atof(tr_set[1]);
		tr.pos2.z = ft_atof(tr_set[2]);
		ft_free_tab2(tr_set);
	}
	tr_set = ft_split(tab[3], ',');
	if (tr_set != NULL)
	{
		tr.pos3.x = ft_atof(tr_set[0]);
		tr.pos3.y = ft_atof(tr_set[1]);
		tr.pos3.z = ft_atof(tr_set[2]);
		ft_free_tab2(tr_set);
	}
	tr_set = ft_split(tab[4], ',');
	if (tr_set != NULL)
	{
		tr.color.r = ft_atof(tr_set[0]);
		tr.color.g = ft_atof(tr_set[1]);
		tr.color.b = ft_atof(tr_set[2]);
		ft_free_tab2(tr_set);
	}
	ft_add_tr(objlst, tr, TRIANGLE, data, num);
	return (0);
}
