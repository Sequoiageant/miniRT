/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 14:51:52 by julnolle          #+#    #+#             */
/*   Updated: 2019/12/26 14:44:07 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_base(char *base)
{
	int i;

	i = 0;
	while (base[i] != 0)
		i++;
	return (i);
}

int		check_base(char *str)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		j = 0;
		while (str[j] != 0)
		{
			if (str[j] == str[i])
				count++;
			j++;
		}
		if (str[i] == '+' || str[i] == '-')
			count++;
		i++;
	}
	if (i == 0 || i == 1 || count != count_base(str))
		return (0);
	else
		return (1);
}

void	convert_base(int nbr, char *base)
{
	long int div;
	long int mod;
	long int nb;

	nb = nbr;
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar('-');
	}
	mod = nb % count_base(base);
	div = nb / count_base(base);
	if (div >= 1)
		convert_base(div, base);
	ft_putchar(base[mod]);
}

void	ft_putnbr_base(int nbr, char *base)
{
	if (check_base(base) == 1)
		convert_base(nbr, base);
}
