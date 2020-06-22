/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 18:48:01 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/22 14:38:27 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_missing_type(t_data *data, t_stm *m, size_t *line)
{
	if (data->objlst_set == FALSE || data->lights_set == FALSE
		|| data->cams_set == FALSE || m->res_set == FALSE
		|| m->al_set == FALSE)
	{
		if (m->error == 0)
		{
			m->error |= TYPE_NB_ERROR_MASK;
			*line = 0;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
