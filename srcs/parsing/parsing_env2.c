/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:00:13 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/17 17:00:03 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		set_res(char **tab, t_data *data, t_stm *machine)
{
	static int set = FAILURE;

	if (set != SUCCESS)
	{
		if (is_int_or_float(tab[1], '+') && is_int_or_float(tab[2], '+'))
		{
			data->win.w = ft_atoi(tab[1]);
			data->win.h = ft_atoi(tab[2]);
			if (data->win.w > 0 && data->win.h > 0)
				set = SUCCESS;
			else
				machine->error |= SIGN_ERROR_MASK;
		}
		else
			machine->error |= SIGN_ERROR_MASK;
	}
	else
	{
		set = FAILURE;
		machine->error |= ENV_ERROR_MASK;
	}
	machine->res_set = TRUE;
	return (set);
}

int		set_al(char **tab, t_data *data, t_stm *machine)
{
	static int	set = FAILURE;

	if (set != SUCCESS)
	{
		if (is_int_or_float(tab[1], '+'))
		{
			set = set_if_in_rnge(tab[1], &data->al.lum, 0.0, 1.0);
			if (set == FAILURE)
				machine->error |= RANGE_ERROR_MASK;
		}
		else
			machine->error |= SIGN_ERROR_MASK;
		if (set != FAILURE)
		{
			set = set_color(tab[2], &data->al.color, &machine->error);
			data->al.color = mult_col_double(data->al.color, data->al.lum);
		}
	}
	else
	{
		set = FAILURE;
		machine->error |= ENV_ERROR_MASK;
	}
	machine->al_set = TRUE;
	return (set);
}
