/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:06:06 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/13 15:40:09 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	error(t_win *win, char *obj, t_stm *machine)
{
	(void)win;
	printf("[%s] -> ERROR\n", obj);
	machine->state = OBJECT;
	return (0);
}

int	empty(t_win *win, char *obj, t_stm *machine)
{
	(void)win;
	printf("[%s] -> EMPTY\n", obj);
	machine->state = OBJECT;
	return (0);
}

int	set_env(t_win *win, char *env, t_stm *machine)
{
	(void)win;

	static char	str_env[NB_ENV] = STR_ENV;
	int			i;

	i = 0;
	while (i < NB_ENV)
	{
		if (*env == str_env[i])
		{
			printf("[%c] -> ENV\n", str_env[i]);
			machine->obj = 0;
			return (1);
		}
		i++;
	}
	error(win, env, machine);
	return (0);
}

int	set_obj(t_win *win, char *obj, t_stm *machine)
{
	(void)win;

	static char	*str_obj[NB_OBJ] = {P_SP, P_PL, P_SQ, P_CY, P_TR};
	int			len;
	int			i;

	i = 0;
	while (i < NB_OBJ)
	{
		len = 2;
		if (ft_strnequ(obj, str_obj[i], len) == TRUE)
		{
			printf("[%s] -> OBJECT\n", str_obj[i]);
			machine->obj |= (1 << i);
			return (len);
		}
		i++;
	}
	set_env(win, obj, machine);
	return (0);
}

int	parser(char **line, t_win *win, int fd)
{
	t_stm			machine;
	t_obj			obj;
	int				ret;
	char			**tab;
	static t_func	func[NB_STATE] = {set_env, set_obj, empty, error};

	ret = 1;
	machine.state = OBJECT;
	machine.obj = 0;
	while (ret > 0)
	{	
		ret = get_next_line(fd, line);
		if (ret != -1)
		{
			tab = ft_split(*line, ' ');
			if (tab)
				if (tab[0] == NULL)
					machine.state = EMPTY;
				func[machine.state](win, tab[0], &machine);
				free(*line);
				free(tab);
			}
		}
		return (SUCCESS);
	}

	int main(int argc, char const *argv[])
	{
		int		fd;
		char	*line;
		t_win	win;

		if (argc == 1)
			fd = 0;
		else if (argc == 2)
			fd = open(argv[1], O_RDONLY);
		else
			return (2);
		parser(&line, &win, fd);

		if (argc == 2)
			close(fd);
		return 0;
	}
