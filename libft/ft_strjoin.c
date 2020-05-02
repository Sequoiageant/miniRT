/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:21:34 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/30 15:03:25 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		dst = ft_strdup(s2);
	else if (!s2)
		dst = ft_strdup(s1);
	else
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		if (!(dst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
			return (NULL);
		ft_memcpy(dst, s1, len_s1);
		ft_memcpy(dst + len_s1, s2, len_s2 + 1);
	}
	return (dst);
}
