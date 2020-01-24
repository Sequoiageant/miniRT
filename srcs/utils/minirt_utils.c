/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:35:45 by julnolle          #+#    #+#             */
/*   Updated: 2020/01/24 16:28:33 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void	ft_putendl(char *s)
{
	ft_putstr(s);
	write(1, "\n", 1);
}

int		ft_atoi(char **str)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while ((**str >= 9 && **str <= 13) || **str == ' ')
		(*str)++;
	if ((*str)[0] == '+' || (*str)[0] == '-')
		i++;
	while ((*str)[i] >= '0' && (*str)[i] <= '9')
	{
		res = res * 10 + (*str)[i] - 48;
		i++;
	}
	(*str) += i;
	return ((*str)[0] == '-' ? -res : res);
}
