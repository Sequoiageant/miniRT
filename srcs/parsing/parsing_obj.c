/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:50:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 12:03:57 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	}
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
	}
	return (ret);
}
