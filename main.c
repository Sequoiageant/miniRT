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
	win->x = ft_atoi2(line);
	win->y = ft_atoi2(line);
	win->set = true;
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

int key_event(int key, t_data *data)
{
	double		angle;
	int r;
	int x;
	int y;
	t_color	color;

	ft_putnbr(key);
	r = 200;
	while (r > 0)
	{
		angle = 0;
		while (angle < 360)
		{
			color.r = (rand() % 50) + 1;
			color.g = (rand() % 254) + 1;
			color.b = (rand() % 254) + 1;
			x = r * cos(angle * M_PI / 180);
			y = r * sin(angle * M_PI / 180);
			mlx_pixel_put(data->mlx_ptr, data->mlx_win, x + 300, y + 300, 0.1*color.r*color.g*color.b);
			angle += 0.1;
		}
		r--;
	}

/*	i = 160;
	while (i < 480)
	{
		j = 120;
		while (j < 360)
		{
			mlx_pixel_put(data->mlx_ptr, data->mlx_win, i, j, 0.1*color.r*color.g*color.b);
			j++;
		}
		i++;
	}*/
	return(0);
}

int	ft_launch_window(t_win *win)
{
	t_data data;

	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, win->x, win->y, "miniRT")) == NULL)
		return (EXIT_FAILURE);
	// mlx_hook(data.mlx_win, 3, 53, key_event, NULL);
	// mlx_hook(data.mlx_win, 17, 1L << 17, key_event, NULL);
	mlx_key_hook(data.mlx_win, key_event, &data);

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
