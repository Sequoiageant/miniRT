/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 18:48:01 by julnolle          #+#    #+#             */
/*   Updated: 2020/05/03 13:06:11 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_missing_type(t_data *data, t_stm *machine, size_t *line_nb)
{
	if (data->objlst_set == FALSE || data->lights_set == FALSE
		|| data->cams_set == FALSE || machine->res_set == FALSE
		|| machine->al_set == FALSE)
	{
		if (machine->error == 0)
		{
			machine->error |= TYPE_NB_ERROR_MASK;
			*line_nb = 0;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
