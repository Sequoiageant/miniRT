/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/19 18:57:17 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			print_error(const char *error, int line_nb)
{
	if (line_nb == 0)
		write(2, "Error:\n", 7);
	else
	{
		write(2, "Error:\nLine ", 12);
		ft_putnbr_fd(line_nb, 2);
		write(2, ": ", 2);
	}
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (FAILURE);
}

static int	parser(t_data *data, int fd)
{
	t_stm			machine;
	int				ret;
	char			*line;
	size_t			line_nb;

	ret = 1;
	line_nb = 0;
	machine.state = EMPTY;
	init_data(data, &machine);
	while (ret > 0)
	{
		line = NULL;
		ret = get_next_line(fd, &line);
		line_nb++;
		if (ret != FAILURE)
		{
			if (run_machine(line, data, &machine) == FAILURE)
				ret = FAILURE;
			free(line);
		}
	}
	if (check_missing_type(data, &machine, &line_nb) == FAILURE)
		ret = FAILURE;
	select_error(machine.error, line_nb);
	return (ret);
}

static int	minirt(t_data *data, int ac, char **av)
{
	int	fd;
	int ret;

	ret = SUCCESS;
	fd = open(av[1], O_RDONLY);
	if (fd != -1)
	{
		if (parser(data, fd) != FAILURE)
		{
			close(fd);
			if (ac == 2)
				ret = launch_window(data);
			else if (ac == 3 && ft_strcmp(av[2], "-save") == 0)
			{
				if ((ret = save_image(data)) == SUCCESS)
					write(1, BMP_SUCCESS, ft_strlen(BMP_SUCCESS));
			}
			else
				ret = print_error(SAVE_ERROR, 0);
		}
		free_minirt(data);
	}
	else
		ret = print_error(FD_ERROR, 0);
	return (ret);
}

int			main(int ac, char **av)
{
	int		ret;
	t_data	data;

	ret = SUCCESS;
	if (ac == 2 || ac == 3)
		ret = minirt(&data, ac, av);
	else
		ret = print_error(ARGS_ERROR, 0);
	return (ret);
}
