/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrsize_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:21:14 by julnolle          #+#    #+#             */
/*   Updated: 2020/01/06 17:51:03 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the len of a nbr converted into base
*/

size_t	ft_nbrsize_base(long n, size_t base_len)
{
	size_t len;

	if (n == 0)
		len = 1;
	else
	{
		len = (n < 0) ? 1 : 0;
		n = (n < 0) ? -n : n;
		while (n > 0)
		{
			n = n / base_len;
			len++;
		}
	}
	return (len);
}
