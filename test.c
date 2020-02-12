/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:06:06 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/12 18:50:01 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	error(t_win *win, char *obj)
{
	(void)win;
	printf("%s - [%s]\n", "ERROR", obj);
	return (0);
}

int	set_obj(t_win *win, char *obj)
{
	(void)win;
	printf("%s - [%s]\n", "OBJET", obj);
	return (0);
}

int	set_env(t_win *win, char *env)
{
	(void)win;
	printf("%s - [%s]\n", "ENVIRONMENT", env);
	return (0);
}


int	parser(char **line, t_win *win, int fd)
{
	t_stm			machine;
	t_obj			obj;
	int				ret;
	size_t			len;
	char			**tab;
	static t_func	func[NB_STATE] = {set_env, set_obj, error};

	// obj.type = SPHERE;
	// obj.u_obj.sp.dia = 12;
	ret = 1;
	while (ret > 0)
	{	
		ret = get_next_line(fd, line);
		machine.state = ERROR;
		if (ret != -1)
		{
			tab = ft_split(*line, ' ');
			if (tab && tab[0] != NULL)
			{
				if (ft_strlen(tab[0]) == 1)
					machine.state = ENV;
				else
					machine.state = OBJECT;
			}
			func[machine.state](win, tab[0]);
			free(*line);
		}
	}
	/*
	obj.type = ERROR;
	obj.u_obj.err = true;
	while (*format != '\0')
	{
		ret = func[obj.type](win, &obj);
		if (ret == FAILURE)
			return (FAILURE);
		format += ret;
	}*/
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
