/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:35:39 by julnolle          #+#    #+#             */
/*   Updated: 2019/11/15 17:26:27 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = NULL;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL || dst == NULL)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		dst[0] = '\0';
	else
	{
		while (s[start] != '\0' && i < len)
		{
			dst[i] = s[start];
			i++;
			start++;
		}
		dst[i] = '\0';
	}
	return (dst);
}
