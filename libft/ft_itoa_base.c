/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:10:53 by julnolle          #+#    #+#             */
/*   Updated: 2020/01/05 16:52:39 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long nb, char *base)
{
	char			*str;
	size_t			len;
	size_t			base_len;

	base_len = ft_strlen(base);
	len = ft_nbrsize_base(nb, base_len);
	str = NULL;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str)
	{
		str[len] = '\0';
		len--;
		if (nb == 0)
			str[len] = '0';
		while (nb > 0)
		{
			str[len] = base[nb % base_len];
			nb = nb / base_len;
			len--;
		}
	}
	return (str);
}
