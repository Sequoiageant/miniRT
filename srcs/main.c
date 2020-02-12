/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/12 16:41:43 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_func_choose(char *line, t_win *win)
{
	char **tab;

	tab = ft_split(line, ' ');
	if (tab[0] == 0)
		return (1);
	else if (ft_strcmp(tab[0], "R") == 0)
		ft_set_win(tab, win);
	else if (ft_strcmp(tab[0], "A") == 0)
		ft_set_ambiant_light(tab);
	else if (ft_strcmp(tab[0], "c") == 0)
		ft_set_camera(tab);
	else if (ft_strcmp(tab[0], "sp") == 0)
		ft_set_sphere(tab);
	else
		return (0);
	return (1);
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

int main(int argc, char const *argv[])
{
	int		fd;
	char	*line;
	int		ret;
	t_win	win;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	ret = 1;
	while (ret > 0)
	{	
		ret = get_next_line(fd, &line);
		if (ret != -1)
		{
			ft_func_choose(line, &win);
			free(line);
		}
	}
	ft_launch_window(&win);
	if (argc == 2)
		close(fd);
	return 0;
}
