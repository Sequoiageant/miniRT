/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:40:18 by julnolle          #+#    #+#             */
/*   Updated: 2019/11/13 10:08:18 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_cpy;
	unsigned char	*src_cpy;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_cpy = (unsigned char *)dst;
	src_cpy = (unsigned char *)src;
	while (len > 0)
	{
		if (src_cpy > dst_cpy)
			*dst_cpy++ = *src_cpy++;
		else
			dst_cpy[len - 1] = src_cpy[len - 1];
		len--;
	}
	return (dst);
}
