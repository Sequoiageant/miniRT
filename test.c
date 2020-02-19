/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:06:06 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/19 14:23:33 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int		ft_strnequ(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	print_bin(int nb)
{
	int	i;

	i = 0;
	printf("flag : [");
	while (i < 32)
	{
		if (i != 0 && i % 8 == 0)
			printf(".");
		if (nb & (1 << (31 - i)))
			printf("1");
		else
			printf("0");
		i++;
	}
	printf("]\n");
}

int	error(t_win *win, char **tab, t_stm *machine, t_obj **objlst)
{
	(void)win;
	printf("[%s] -> ERROR\n", tab[0]);
	machine->state = OBJECT;
	return (0);
}

int	empty(t_win *win, char **tab, t_stm *machine, t_obj **objlst)
{
	(void)win;
	printf("[%s] -> EMPTY\n", tab[0]);
	machine->state = OBJECT;
	return (0);
}

int	set_env(t_win *win, char **tab, t_stm *machine, t_obj **objlst)
{
	(void)win;

	static char	str_env[NB_ENV] = STR_ENV;
	int			i;

	i = 0;
	while (i < NB_ENV)
	{
		if ((*tab)[0] == str_env[i])
		{
			printf("[%c] -> ENV\n", str_env[i]);
			return (1);
		}
		i++;
	}
	error(win, tab, machine, objlst);
	return (0);
}

int	ft_list_objects(char **tab, t_win *win, int i, t_obj **objlst)
{
	static t_func2	func[NB_OBJ] = {set_sp, set_pl, set_sq, set_cy, set_tr};

	func[i](tab, objlst);
	while ((*objlst))
	{
		printf("	-->%d\n", (*objlst)->type);
		(*objlst) = (*objlst)->next;
	}
	printf("%d\n", ft_lstsize((*objlst)));

	return (0);
}

int	set_obj(t_win *win, char **tab, t_stm *machine, t_obj **objlst)
{
	(void)win;

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
			ft_list_objects(tab, win, i, objlst);
			return (len);
		}
		i++;
	}
	set_env(win, tab, machine, objlst);
	return (0);
}

int	parser(char **line, t_win *win, int fd)
{
	t_stm			machine;
	t_obj			*objlst;
	int				ret;
	char			**tab;
	static t_func	func[NB_STATE] = {set_env, set_obj, empty, error};

	ret = 1;
	machine.state = OBJECT;
	objlst = NULL;
	while (ret > 0)
	{	
		ret = get_next_line(fd, line);
		if (ret != -1)
		{
			tab = ft_split(*line, ' ');
			if (tab)
			{
				if (tab[0] == NULL)
					machine.state = EMPTY;
				if (func[machine.state](win, tab, &machine, &objlst) == FAILURE)
					return (FAILURE);
				free(*line);
				free(tab);
			}
		}
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	int		fd;
	char	*line;
	t_win	win;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd != -1)
		{
			parser(&line, &win, fd);
			close(fd);
		}
	}
	else
		return (FAILURE);
	return (SUCCESS);
}
