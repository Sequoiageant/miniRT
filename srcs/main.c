/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/10 19:54:39 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*int			print_main_error(const char *error)
{
	write(2, "Error:\n", 7);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (FAILURE);
}*/

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

int			main(int ac, char **av)
{
	int		fd;
	int		ret;
	t_data	data;

	ret = SUCCESS;
	if (ac == 2 || ac == 3)
	{
		fd = open(av[1], O_RDONLY);
		if (fd != -1)
		{
			if (parser(&data, fd) != FAILURE)
			{
				if (ac == 2)
					ft_launch_window(&data);
				else if (ac == 3 && ft_strcmp(av[2], "-save") == 0)
					ft_save_image(&data);
				else
					ret = print_error(SAVE_ERROR, 0);
			}
			close(fd);
			free_minirt(&data);
		}
		else
			ret = print_error(FD_ERROR, 0);
	}
	else
		ret = print_error(ARGS_ERROR, 0);
	// system("leaks minirt");
	return (ret);
}
/*
int	main(int ac, char **av)
{
	int		fd;
	int		ret;
	t_data	data;

	ret = 0;
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd != -1)
		{
			ret = parser(&data, fd);
			free_minirt(&data);
			close(fd);
		}
		else
		{
			perror("Error");
			// ft_putstr(strerror(errno));
			ret = FAILURE;
		}
	}
	else
		ret = print_error(ARGS_ERROR, 0);
	// system("leaks minirt");
	return (ret);
}
*/