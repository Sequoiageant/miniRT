/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 20:29:44 by julien            #+#    #+#             */
/*   Updated: 2020/03/24 20:41:31 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*int	ft_list_env(char **tab, t_data *data, int i)
{
	static t_func3	func[NB_ENV] = {set_res, set_al, set_cam, set_light};

	func[i](tab, data);
	return (0);
}*/

int	ft_list_objects(char **tab, t_data *data, int i)
{
	static t_func2	func[NB_OBJ] = {set_sp, set_pl, set_sq, set_cy, set_tr};
	static t_obj	*objlst;
	static int		obj_num = 1;

	func[i](tab, &objlst, data, obj_num);
	obj_num++;
	return (0);
}

int	error(t_data *data, char **tab, t_stm *machine)
{
	(void)data;
	(void)machine;
	printf("[%s] -> ERROR\n", tab[0]);
	return (MACHINE_CONTINUE);
}

int	set_obj(t_data *data, char **tab, t_stm *machine)
{
	static char	*str_obj[NB_OBJ] = {P_SP, P_PL, P_SQ, P_CY, P_TR};
	int			len;
	int			i;
	
	i = 0;
	while (i < NB_OBJ)
	{
		len = 2;
		if (ft_strnequ(tab[0], str_obj[i], len) == TRUE)
		{
			printf("[%s] -> OBJECT\n", str_obj[i]);
			ft_list_objects(tab, data, i);
			return (MACHINE_CONTINUE);
		}
		i++;
	}
	machine->state = ERROR;
	return (MACHINE_AGAIN);
}

int	set_env(t_data *data, char **tab, t_stm *machine)
{
	static char	*str_env[NB_ENV] = {P_R, P_A, P_C, P_L};
	static t_func3	func[NB_ENV] = {set_res, set_al, set_cam, set_light};

	int			i;

	i = 0;
	while (i < NB_ENV)
	{
		if (ft_strcmp(tab[0], str_env[i]) == 0)
		{
			printf("[%s] -> ENV\n", str_env[i]);
			func[i](tab, data);
			return (MACHINE_CONTINUE);
		}
		i++;
	}
	machine->state = OBJECT;
	return (MACHINE_AGAIN);
}

int	empty(t_data *data, char **tab, t_stm *machine)
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

int	parser(t_data *data, int fd)
{
	t_stm			machine;
	int				ret;
	int 			ret_machine;
	char			**tab;
	char			*line;
	static t_func	func[NB_STATE] = {empty, set_env, set_obj, error};

	ret = 1;
	machine.state = EMPTY;
	while (ret > 0)
	{
		line = NULL;
		ret = get_next_line(fd, &line);
		if (ret != FAILURE)
		{
			tab = ft_split_whitespaces(line);
			if (tab)
			{
				ret_machine = MACHINE_AGAIN;
				while (ret_machine == MACHINE_AGAIN)
					ret_machine = func[machine.state](data, tab, &machine);
				machine.state = EMPTY;
				if (ret_machine == MACHINE_ERROR)
					ret = FAILURE;
				free(tab);
			}
			free(line);
		}
	}
	return (ret);
}
