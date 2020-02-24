/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/24 19:28:23 by julnolle         ###   ########.fr       */
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

/*void	print_list(t_obj *objlst)
{

	printf("	-->list size: %d\n", ft_lstsize(objlst));
	while (objlst)
	{
		if (objlst->type == SPHERE)
		{
			printf("	-->type: %d\n", objlst->type);
			printf("	-->%f\n", ((t_sp *)objlst->content)->dia);
		}
		objlst = objlst->next;
	}
}*/

/*void	sort_list(t_obj *objlst)
{
	print_list(objlst);
}*/

int	ft_list_env(char **tab, t_data *data, int i)
{
	static t_func3	func[NB_ENV] = {set_res, set_al, set_cam, set_light};

	func[i](tab, data);
	return (0);
}

int	ft_list_objects(char **tab, t_data *data, int i)
{
	static t_func2	func[NB_OBJ] = {set_sp, set_pl, set_sq, set_cy, set_tr};
	static t_obj	*objlst;

	func[i](tab, &objlst, data);
	return (0);
}

int ft_close(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	exit(EXIT_SUCCESS);
}

int key_event(int key, t_mlx *mlx)
{
	// ft_putnbr(key);
	if(key == 8)
		ft_draw_circle(mlx);
	if(key == 1)
		ft_draw_sphere(mlx);
	else if(key == 12)
		ft_draw_square(mlx);
	else if(key == 17)
		ft_draw_triangle(mlx);
	else if(key == 4)
		ft_draw_hex(mlx);
	else if(key == 49)
		mlx_string_put(mlx->mlx_ptr, mlx->mlx_win, 650, 500, 0xFFFF00, "CA MARCHE !");
	else if(key == 53)
		ft_close(mlx);
	return(0);
}

int	search_list(int cam_num, t_data data)
{
	while (data.cams)
	{
		if (data.cams->nbr == cam_num)
		{
			return (1);
		}
		data.cams = data.cams->next;
	}
	return (0);
}

int choose_cam(int key, t_data *data)
{
	static int cam_num = 1;

	if(key == 123)
		cam_num--;
	else if(key == 124)
		cam_num++;
	if (cam_num > 0)
	{
		if (search_list(cam_num, *data) == 1)
			data->cam_num = cam_num;
	}
	if (cam_num < data->cam_num)
	{
		if (search_list(cam_num, *data) == 1)
			data->cam_num = cam_num;
	}
	ft_raytracing(data);
	printf("%d\n", cam_num);
	return(0);
}

int	ft_launch_window(t_data *data)
{
	t_mlx	mlx;
	t_win	win;

	win = data->win;
	if ((mlx.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, win.w, win.h, "miniRT")) == NULL)
		return (EXIT_FAILURE);
	mlx.img = mlx_new_image(mlx.mlx_ptr, win.w, win.h);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	mlx_hook(mlx.mlx_win, 2, 1L<<0, key_event, &mlx);
	mlx_hook(mlx.mlx_win, 3, 1L<<1, choose_cam, data);
	mlx_hook(mlx.mlx_win, 17, 1L << 17, ft_close, &mlx);
	data->mlx = mlx;
	// mlx_loop_hook(&mlx, ft_raytracing, data);
	data->cam_num = 1;
	ft_raytracing(data);
	mlx_loop(mlx.mlx_ptr);
	return (EXIT_SUCCESS);
}

int	error(t_data *data, char **tab, t_stm *machine)
{
	(void)data;
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
	static char	str_env[NB_ENV] = STR_ENV;
	int			i;

	i = 0;
	while (i < NB_ENV)
	{
		if ((*tab)[0] == str_env[i])
		{
			printf("[%c] -> ENV\n", str_env[i]);
			ft_list_env(tab, data, i);
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
	printf("[%s] -> EMPTY\n", tab[0]);
	if (tab[0] == NULL)
		return (MACHINE_CONTINUE);
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
			tab = ft_split(line, ' ');
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

int	main(int ac, char **av)
{
	int		fd;
	t_data	data;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd != -1)
		{
			parser(&data, fd);
			close(fd);
		}
		ft_launch_window(&data);
	}
	else
		return (FAILURE);
	system("leaks a.out");
	return (SUCCESS);
}
