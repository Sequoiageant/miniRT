/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/13 20:01:56 by julnolle         ###   ########.fr       */
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

int	set_pl(char **tab, t_obj **objlst)
{
	printf("	-->%s\n", tab[0]);
	return (0);
}

int	set_cy(char **tab, t_obj **objlst)
{
	printf("	-->%s\n", tab[0]);
	return (0);
}

int	set_tr(char **tab, t_obj **objlst)
{
	printf("	-->%s\n", tab[0]);
	return (0);
}

int	ft_list_objects(char **tab, t_win *win, int i)
{
	static t_func2	func[NB_OBJ] = {set_sp, set_pl, set_sq, set_cy, set_tr};
	static t_obj	*objlst;

	func[i](tab, &objlst);
	while (objlst->next != NULL)
	{
		printf("	-->%d\n", objlst->type);
		objlst = objlst->next;
	}
	printf("%s\n", "TOTO");
	return (0);
}

int ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(EXIT_SUCCESS);
}

int key_event(int key, t_data *data)
{
	ft_putnbr(key);
	if(key == 8)
		ft_draw_circle(data);
	if(key == 1)
		ft_draw_sphere(data);
	else if(key == 12)
		ft_draw_square(data);
	else if(key == 17)
		ft_draw_triangle(data);
	else if(key == 4)
		ft_draw_hex(data);
	else if(key == 49)
		mlx_string_put(data->mlx_ptr, data->mlx_win, 650, 500, 0xFFFF00, "CA MARCHE !");
	else if(key == 53)
		ft_close(data);
	return(0);
}

int	ft_launch_window(t_win *win)
{
	t_data data;

	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, win->w, win->h, "miniRT")) == NULL)
		return (EXIT_FAILURE);
	data.img = mlx_new_image(data.mlx_ptr, win->w, win->h);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	mlx_hook(data.mlx_win, 2, 0L, key_event, &data);
	mlx_hook(data.mlx_win, 17, 1L << 17, ft_close, &data);
	ft_raytracing(&data, win);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
	return (0);
}

int	error(t_win *win, char **tab, t_stm *machine)
{
	(void)win;
	printf("[%s] -> ERROR\n", tab[0]);
	machine->state = OBJECT;
	return (0);
}

int	empty(t_win *win, char **tab, t_stm *machine)
{
	(void)win;
	printf("[%s] -> EMPTY\n", tab[0]);
	machine->state = OBJECT;
	return (0);
}

int	set_env(t_win *win, char **tab, t_stm *machine)
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
	error(win, tab, machine);
	return (0);
}

int	set_obj(t_win *win, char **tab, t_stm *machine)
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
			ft_list_objects(tab, win, i);
			return (len);
		}
		i++;
	}
	set_env(win, tab, machine);
	return (0);
}

int	parser(char **line, t_win *win, int fd)
{
	t_stm			machine;
	int				ret;
	char			**tab;
	static t_func	func[NB_STATE] = {set_env, set_obj, empty, error};

	ret = 1;
	machine.state = OBJECT;
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
				if (func[machine.state](win, tab, &machine) == FAILURE)
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
