/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/20 18:55:54 by julnolle         ###   ########.fr       */
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
	// data->objlst = objlst;
	// if (data->objlst->type == SPHERE)
	// {
	// 	printf("	-->type: %d\n", objlst->type);
	// 	printf("	-->%f\n", ((t_sp *)data->objlst->content)->dia);
	// }
	// sort_list(objlst);
	return (0);
}

int ft_close(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	exit(EXIT_SUCCESS);
}

int key_event(int key, t_mlx *mlx)
{
	ft_putnbr(key);
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
	mlx_hook(mlx.mlx_win, 2, 0L, key_event, &mlx);
	mlx_hook(mlx.mlx_win, 17, 1L << 17, ft_close, &mlx);
	ft_raytracing(&mlx, data);
	mlx_loop(mlx.mlx_ptr);
	return (EXIT_SUCCESS);
	return (0);
}

int	error(t_data *data, char **tab, t_stm *machine)
{
	(void)data;
	printf("[%s] -> ERROR\n", tab[0]);
	machine->state = OBJECT;
	return (0);
}

int	empty(t_data *data, char **tab, t_stm *machine)
{
	(void)data;
	printf("[%s] -> EMPTY\n", tab[0]);
	machine->state = OBJECT;
	return (0);
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
			return (1);
		}
		i++;
	}
	error(data, tab, machine);
	return (0);
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
			return (len);
		}
		i++;
	}
	set_env(data, tab, machine);
	return (0);
}

int	parser(char **line, t_data *data, int fd)
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
				if (func[machine.state](data, tab, &machine) == FAILURE)
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
	t_data	data;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd != -1)
		{
			parser(&line, &data, fd);
			close(fd);
		}
		ft_launch_window(&data);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}
