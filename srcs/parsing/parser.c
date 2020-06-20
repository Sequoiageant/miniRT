/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 19:06:54 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 12:02:11 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	error(t_data *data, char **tab, t_stm *machine)
{
	(void)data;
	(void)machine;
	if (tab[0][0] == '#')
	{
		printf("[%s] -> COMMENT\n", tab[0]);
		return (MACHINE_CONTINUE);
	}
	else
	{
		printf("[%s] -> ERROR\n", tab[0]);
		machine->error |= TYPE_ERROR_MASK;
		return (MACHINE_ERROR);
	}
}

static int	set_obj(t_data *data, char **tab, t_stm *machine)
{
	static char		*str_obj[NB_OBJ] = {P_SP, P_PL, P_SQ, P_CY, P_TR};
	static t_func2	func[NB_OBJ] = {set_sp, set_pl, set_sq, set_cy, set_tr};
	static t_obj	*objlst;
	int				ret;
	int				i;

	i = 0;
	machine->error = 0;
	ret = FAILURE;
	while (i < NB_OBJ)
	{
		if (ft_strnequ(tab[0], str_obj[i], 2) == TRUE)
		{
			printf("[%s] -> OBJECT\n", str_obj[i]);
			if (split_size_error(tab, i + NB_ENV, &machine->error))
				ret = func[i](tab, &objlst, data, machine);
			if (ret == SUCCESS)
				return (MACHINE_CONTINUE);
			else
				return (MACHINE_ERROR);
		}
		i++;
	}
	machine->state = ERROR;
	return (MACHINE_AGAIN);
}

static int	set_env(t_data *data, char **tab, t_stm *machine)
{
	static char		*str_env[NB_ENV] = {P_R, P_A, P_C, P_L};
	static t_func3	func[NB_ENV] = {set_res, set_al, set_cam, set_light};
	int				ret;
	int				i;

	i = 0;
	machine->error = 0;
	ret = FAILURE;
	while (i < NB_ENV)
	{
		if (ft_strcmp(tab[0], str_env[i]) == 0)
		{
			printf("[%s] -> ENV\n", str_env[i]);
			if (split_size_error(tab, i, &machine->error))
				ret = func[i](tab, data, machine);
			if (ret == SUCCESS)
				return (MACHINE_CONTINUE);
			else
				return (MACHINE_ERROR);
		}
		i++;
	}
	machine->state = OBJECT;
	return (MACHINE_AGAIN);
}

static int	empty(t_data *data, char **tab, t_stm *machine)
{
	(void)data;
	if (tab[0] == NULL)
	{
		printf("[%s] -> EMPTY\n", tab[0]);
		return (MACHINE_CONTINUE);
	}
	machine->state = ENV;
	return (MACHINE_AGAIN);
}

int			run_machine(char *line, t_data *data, t_stm *machine)
{
	static t_func	func[NB_STATE] = {empty, set_env, set_obj, error};
	int				ret_machine;
	char			**tab;
	int				ret;

	ret = SUCCESS;
	tab = ft_split_whitespaces(line);
	if (tab)
	{
		ret_machine = MACHINE_AGAIN;
		while (ret_machine == MACHINE_AGAIN)
		{
			ret_machine = func[machine->state](data, tab, machine);
			if (ret_machine == MACHINE_ERROR)
				ret = FAILURE;
		}
		machine->state = EMPTY;
		free_split(tab);
	}
	return (ret);
}
