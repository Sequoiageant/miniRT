/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/07 11:51:04 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_main_error(const char *error)
{
	write(2, "Error:\n", 7);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (FAILURE);
}

int	print_error(const char *error, int line_nb)
{
	write(2, "Error:\nLine ", 12);
	ft_putnbr_fd(line_nb, 2);
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (FAILURE);
}

int	main(int ac, char **av)
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
					ret = print_main_error(SAVE_ERROR);
			}
			close(fd);
			free_minirt(&data);
		}
		else
			ret = print_main_error(FD_ERROR);
	}
	else
		ret = print_main_error(ARGS_ERROR);
	// system("leaks minirt");
	return (ret);
}

/*int	main(int ac, char **av)
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
		ret = print_error(ARGS_ERROR);
	// system("leaks minirt");
	return (ret);
}
*/