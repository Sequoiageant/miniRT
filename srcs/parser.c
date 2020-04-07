/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 20:29:44 by julien            #+#    #+#             */
/*   Updated: 2020/04/07 16:34:23 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*int	ft_list_env(char **tab, t_data *data, int i)
{
	static t_func3	func[NB_ENV] = {set_res, set_al, set_cam, set_light};

	func[i](tab, data);
	return (0);
}*/

/*int	ft_list_objects(char **tab, t_data *data, int i)
{
	static t_func2	func[NB_OBJ] = {set_sp, set_pl, set_sq, set_cy, set_tr};
	static t_obj	*objlst;

	func[i](tab, &objlst, data);
	return (0);
}
*/

int	ft_lstsize(t_obj *lst)
{
	int size;

	size = 0;
	if (lst != NULL)
	{
		while (lst)
		{
			size++;
			lst = lst->next;
		}
	}
	return (size);
}

void	print_obj(t_obj *objlst)
{
	while (objlst)
	{
		printf("	-->Type %d\n", objlst->type);
		objlst = objlst->next;
	}
}

void select_error(int error, size_t line_nb)
{
	const char *str_error[] = {SAVE_ERROR, ARGS_ERROR, FD_ERROR,
								VECTOR_ERROR, TYPE_ERROR, ENV_ERROR,
								SIGN_ERROR, INT_ERROR, COL_ERROR,
								RANGE_ERROR, RANGE2_ERROR, FOV_ERROR,
								MALLOC_ERROR};
	size_t		i;
	size_t		nb_error;

	i = 0;
	nb_error = sizeof(str_error) / sizeof(str_error[0]);
	while (i < nb_error)
	{
		if (error & (1 << i))
			print_error(str_error[i], line_nb);
		i++;
	}
}

int	error(t_data *data, char **tab, t_stm *machine)
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

int	set_obj(t_data *data, char **tab, t_stm *machine)
{
	static char		*str_obj[NB_OBJ] = {P_SP, P_PL, P_SQ, P_CY, P_TR};
	static t_func2	func[NB_OBJ] = {set_sp, set_pl, set_sq, set_cy, set_tr};
	static t_obj	*objlst;
	int				ret;
	int				i;

	i = 0;
	machine->error = 0;
	while (i < NB_OBJ)
	{
		if (ft_strnequ(tab[0], str_obj[i], 2) == TRUE)
		{
			printf("[%s] -> OBJECT\n", str_obj[i]);
			ret = func[i](tab, &objlst, data, &machine->error);
			if (ret == SUCCESS)
			{
				// print_obj(data->objlst);
				return (MACHINE_CONTINUE);
			}
			else
				return (MACHINE_ERROR);
		}
		i++;
	}
	machine->state = ERROR;
	return (MACHINE_AGAIN);
}

int	set_env(t_data *data, char **tab, t_stm *machine)
{
	static char		*str_env[NB_ENV] = {P_R, P_A, P_C, P_L};
	static t_func3	func[NB_ENV] = {set_res, set_al, set_cam, set_light};
	int				ret;
	int				i;

	i = 0;
	machine->error = 0;
	while (i < NB_ENV)
	{
		if (ft_strcmp(tab[0], str_env[i]) == 0)
		{
			printf("[%s] -> ENV\n", str_env[i]);
			ret = func[i](tab, data, &machine->error);
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

void init_data(t_data *data)
{
	data->objlst_set = FALSE;
	data->cams_set = FALSE;
	data->lights_set = FALSE;
}

int	check_line(char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		// printf("%c\n", str[i]);
		if (!ft_isdigit(str[i]) && str[i] != '.' && str[i] != ','
			&& str[i] != '+' && str[i] != '-'
			&& str[i] != ' ' && str[i] != '\t' && str[i] != '#')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_tab(char **tab)
{
	size_t i;

	if (tab[0] == NULL)
		return (TRUE);
	i = 1;
	if (tab[0][0] == '#')
		i++;
	while (tab[i] != 0)
	{
		// printf("%s\n", "TOTO");
		if (!check_line(tab[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	parser(t_data *data, int fd)
{
	t_stm			machine;
	int				ret;
	int				ret_machine;
	char			**tab;
	char			*line;
	static t_func	func[NB_STATE] = {empty, set_env, set_obj, error};
	size_t			line_nb;

	ret = 1;
	line_nb = 0;
	machine.state = EMPTY;
	init_data(data);
	while (ret > 0)
	{
		line = NULL;
		ret = get_next_line(fd, &line);
		line_nb++;
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
				{
					select_error(machine.error, line_nb);
					ret = FAILURE;
				}
				free_split(tab);
			}
			free(line);
		}

	}
	return (ret);
}
