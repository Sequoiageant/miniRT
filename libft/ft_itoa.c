/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:01:04 by julnolle          #+#    #+#             */
/*   Updated: 2020/01/06 16:50:41 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;
	long	nb;

	len = ft_nbrsize(n);
	nb = (n < 0) ? -(long)n : (long)n;
	str = NULL;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str)
	{
		str[len] = '\0';
		len--;
		str[len] = (nb == 0) ? '0' : str[len];
		while (nb > 0)
		{
			str[len] = (nb % 10) + '0';
			nb = nb / 10;
			len--;
		}
		if (n < 0)
			str[0] = '-';
	}
	return (str);
}
