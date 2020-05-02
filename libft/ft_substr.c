/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:35:39 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/30 15:12:08 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	dst = NULL;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL || dst == NULL)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		dst[0] = '\0';
	else
	{
		dst = ft_memcpy(dst, s + start, len);
		dst[len] = '\0';
	}
	return (dst);
}
