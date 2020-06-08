/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:41:01 by julnolle          #+#    #+#             */
/*   Updated: 2020/05/03 13:03:44 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	free_objlist(t_obj **objlst)
{
	t_obj *tmp;

	while (*objlst != NULL)
	{
		tmp = *objlst;
		*objlst = (*objlst)->next;
		free(tmp);
		tmp = NULL;
	}
	*objlst = NULL;
}

static void	free_camlist(t_cam **camlst)
{
	t_cam *tmp;

	while (*camlst != NULL)
	{
		tmp = *camlst;
		*camlst = (*camlst)->next;
		free(tmp);
		tmp = NULL;
	}
	*camlst = NULL;
}

static void	free_lightlist(t_light **lightlst)
{
	t_light *tmp;

	while (*lightlst != NULL)
	{
		tmp = *lightlst;
		*lightlst = (*lightlst)->next;
		free(tmp);
		tmp = NULL;
	}
	*lightlst = NULL;
}

void		free_minirt(t_data *data)
{
	if (data->objlst_set)
		free_objlist(&data->objlst);
	if (data->lights_set)
		free_lightlist(&data->lights);
	if (data->cams_set > 0)
		free_camlist(&data->cams);
}
