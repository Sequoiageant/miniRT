/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:08:09 by julnolle          #+#    #+#             */
/*   Updated: 2019/11/18 10:50:41 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ndle_len;

	if (*needle == '\0')
		return ((char *)haystack);
	ndle_len = ft_strlen(needle);
	while (*haystack != '\0' && len-- >= ndle_len)
	{
		if (*haystack == *needle && ft_memcmp(haystack, needle, ndle_len) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
