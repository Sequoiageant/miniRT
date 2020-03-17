/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:50:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/04 18:19:52 by julnolle         ###   ########.fr       */
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

void	ft_add_sp(t_obj **objlst, t_sp sp, t_data *data, int num)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->num = num;
		new->type = SPHERE;
		new->col = sp.color;
		new->u_obj.sp = sp;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);

	ft_putendl("	-->element added");
}

void	ft_add_sq(t_obj **objlst, t_sq sq, t_data *data, int num)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->num = num;
		new->type = SQUARE;
		new->col = sq.color;
		new->u_obj.sq = sq;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);

	ft_putendl("	-->element added");
}

void	ft_add_pl(t_obj **objlst, t_pl pl, t_data *data, int num)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->num = num;
		new->type = PLANE;
		new->col = pl.color;
		new->u_obj.pl = pl;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);

	ft_putendl("	-->element added");
}

void	ft_add_cy(t_obj **objlst, t_cy cy, t_data *data, int num)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->num = num;
		new->type = CYLINDER;
		new->col = cy.color;
		new->u_obj.cy = cy;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);

	ft_putendl("	-->element added");
}

void	ft_add_tr(t_obj **objlst, t_tr tr, t_data *data, int num)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->num = num;
		new->type = TRIANGLE;
		new->col = tr.color;
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
		sp.pos = new_vec_from_char(sp_set[0], sp_set[1], sp_set[2]);
		ft_free_tab2(sp_set);
	}
	sp.dia = ft_atof(tab[2]);
	sp_set = ft_split(tab[3], ',');
	if (sp_set != NULL)
	{
		sp.color = char_to_col(sp_set[0], sp_set[1], sp_set[2]);
		ft_free_tab2(sp_set);
	}
	ft_add_sp(objlst, sp, data, num);
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
		sq.pos = new_vec_from_char(sq_set[0], sq_set[1], sq_set[2]);
		ft_free_tab2(sq_set);
	}
	sq_set = ft_split(tab[2], ',');
	if (sq_set != NULL)
	{
		sq.dir = new_vec_from_char(sq_set[0], sq_set[1], sq_set[2]);
		ft_free_tab2(sq_set);
	}
	sq.h = ft_atof(tab[3]);
	sq_set = ft_split(tab[4], ',');
	if (sq_set != NULL)
	{
		sq.color = char_to_col(sq_set[0], sq_set[1], sq_set[2]);
		ft_free_tab2(sq_set);
	}
	ft_add_sq(objlst, sq, data, num);
	return (0);
}

int	set_pl(char **tab, t_obj **objlst, t_data *data, int num)
{
	t_pl	pl;
	char	**pl_set;

	pl_set = ft_split(tab[1], ',');
	if (pl_set != NULL)
	{
		pl.pos = new_vec_from_char(pl_set[0], pl_set[1], pl_set[2]);
		ft_free_tab2(pl_set);
	}
	pl_set = ft_split(tab[2], ',');
	if (pl_set != NULL)
	{
		pl.normal = new_vec_from_char(pl_set[0], pl_set[1], pl_set[2]);
		ft_free_tab2(pl_set);
	}
	pl_set = ft_split(tab[3], ',');
	if (pl_set != NULL)
	{
		pl.color = char_to_col(pl_set[0], pl_set[1], pl_set[2]);
		ft_free_tab2(pl_set);
	}
	ft_add_pl(objlst, pl, data, num);
	return (0);
}

int	set_cy(char **tab, t_obj **objlst, t_data *data, int num)
{
	t_cy	cy;
	char	**cy_set;

	cy_set = ft_split(tab[1], ',');
	if (cy_set != NULL)
	{
		cy.pos = new_vec_from_char(cy_set[0], cy_set[1], cy_set[2]);
		ft_free_tab2(cy_set);
	}
	cy_set = ft_split(tab[2], ',');
	if (cy_set != NULL)
	{
		cy.dir = new_vec_from_char(cy_set[0], cy_set[1], cy_set[2]);
		ft_free_tab2(cy_set);
	}
	cy_set = ft_split(tab[3], ',');
	if (cy_set != NULL)
	{
		cy.color = char_to_col(cy_set[0], cy_set[1], cy_set[2]);
		ft_free_tab2(cy_set);
	}
	cy.dia = ft_atof(tab[4]);
	cy.h = ft_atof(tab[5]);
	ft_add_cy(objlst, cy, data, num);
	return (0);
}

int	set_tr(char **tab, t_obj **objlst, t_data *data, int num)
{
	t_tr	tr;
	char	**tr_set;

	tr_set = ft_split(tab[1], ',');
	if (tr_set != NULL)
	{
		tr.pos1 = new_vec_from_char(tr_set[0], tr_set[1], tr_set[2]);
		ft_free_tab2(tr_set);
	}
	tr_set = ft_split(tab[2], ',');
	if (tr_set != NULL)
	{
		tr.pos2 = new_vec_from_char(tr_set[0], tr_set[1], tr_set[2]);
		ft_free_tab2(tr_set);
	}
	tr_set = ft_split(tab[3], ',');
	if (tr_set != NULL)
	{
		tr.pos3 = new_vec_from_char(tr_set[0], tr_set[1], tr_set[2]);
		ft_free_tab2(tr_set);
	}
	tr_set = ft_split(tab[4], ',');
	if (tr_set != NULL)
	{
		tr.color = char_to_col(tr_set[0], tr_set[1], tr_set[2]);
		ft_free_tab2(tr_set);
	}
	ft_add_tr(objlst, tr, data, num);
	return (0);
}
