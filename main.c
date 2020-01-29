/*                                                                            */
/*                                                        :::      ::::::::   */
/* ************************************************************************** */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 12:18:23 by julnolle          #+#    #+#             */
/*   Updated: 2020/01/27 12:57:19 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

void	ft_set_win(char **line, t_win *win)
{
	(*line)++;
	win->w = ft_atoi2(line);
	win->h = ft_atoi2(line);
	win->set = true;
	if (win->w > 2560)
		win->w = 2560;
	if (win->h > 1440)
		win->h = 1440;
}

void	ft_set_light(char **line, t_win *win)
{
	(void)line;
	(void)win;
	ft_putendl("lumiere");
}

void	ft_set_camera(char **line, t_win *win)
{
	(void)line;
	(void)win;
	ft_putendl("camera");
}

/*int	ft_func_choose(char *line, t_win *win)
{
	char *states;
	char *evts;

	tab[0] = 'R';
	tab[1] = 'A';
}*/

int	ft_func_choose(char *line, t_win *win)
{
	if (line[0] == 'R' && line[1] == ' ')
		ft_set_win(&line, win);
	else if (line[0] == 'A' && line[1] == ' ')
		ft_set_light(&line, win);
	else if (line[0] == 'c' && line[1] == ' ')
		ft_set_camera(&line, win);
	else if (line[0] == '\n')
		return (1);
	else
		return (0);
	return (1);
}

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
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
	else if(key == 1)
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
	mlx_hook(data.mlx_win, 17, 1L << 17, ft_close, NULL);

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
