/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 17:25:08 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 12:04:26 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_in_range_col(t_col *col)
{
	return (col->r >= 0 && col->r <= 255
		&& col->g >= 0 && col->g <= 255
		&& col->b >= 0 && col->b <= 255);
}

int	is_int_or_float(char *str, char sign)
{
	int	i;

	i = 0;
	if (sign == '+')
	{
		if (str[0] == '+')
			i++;
	}
	else if (sign == '-')
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (FALSE);
		if (str[i] == '.' && (str[i + 1] == '.' || str[i + 1] == '\0'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_int(char *str, char sign)
{
	int	i;

	i = 0;
	if (sign == '+')
	{
		if (str[0] == '+')
			i++;
	}
	else if (sign == '-')
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ckeck_vec(char *str)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '.' && str[i] != ','
			&& str[i] != '+' && str[i] != '-')
			return (FALSE);
		if (ft_isdigit(str[i]) && (str[i + 1] == '+' || str[i + 1] == '-'))
			return (FALSE);
		if (str[i] == '.' && (str[i + 1] == '.' || str[i + 1] == '\0'))
			return (FALSE);
		if ((str[i] == '+' || str[i] == '-')
			&& (str[i + 1] == '+' || str[i + 1] == '-'))
			return (FALSE);
		if (str[i] == ',')
			count++;
		i++;
	}
	i--;
	if (count != 2 || str[i] == ',')
		return (FALSE);
	return (TRUE);
}

int	ckeck_col(char *str)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (str[0] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != ',')
			return (FALSE);
		if (ft_isdigit(str[i]) && str[i + 1] == '+')
			return (FALSE);
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (FALSE);
	return (TRUE);
}
