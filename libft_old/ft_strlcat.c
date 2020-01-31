/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:06:48 by julnolle          #+#    #+#             */
/*   Updated: 2019/11/08 17:13:17 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	long int	src_size;
	size_t		dest_size;
	long int	j;

	src_size = ft_strlen(src);
	dest_size = ft_strlen(dst);
	j = 0;
	if (dstsize <= dest_size)
		src_size = src_size + dstsize;
	else
		src_size = src_size + dest_size;
	if (dstsize > dest_size)
	{
		while (src[j] != '\0' && dest_size < dstsize - 1)
		{
			dst[dest_size] = src[j];
			j++;
			dest_size++;
		}
		dst[dest_size] = '\0';
	}
	return (src_size);
}
