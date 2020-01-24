/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 12:18:23 by julnolle          #+#    #+#             */
/*   Updated: 2020/01/24 16:34:51 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_parse_line(char *line)
{
	int x;
	int y;
	data_t	data;
	int		i;
	int		j;

	ft_putendl(line);
	if (line[0] == 'R')
	{
		line++;
		x = ft_atoi(&line);
		y = ft_atoi(&line);
		// printf("%dx%d\n", x, y);
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, x, y, "miniRT")) == NULL)
		return (EXIT_FAILURE);
	i = 160;
	while (i < 480)
	{
		j = 120;
		while (j < 360)
		{
			mlx_pixel_put(data.mlx_ptr,data.mlx_win, i, j, 100*100*50);
			j++;
		}
		i++;
	}
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
	}
	return (0);
}

int main(int argc, char const *argv[])
{
	int		fd;
	char	*line;
	int		ret;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	ret = get_next_line(fd, &line);
	if (ret != -1)
		ft_parse_line(line);
	if (argc == 2)
		close(fd);


	return 0;
}
