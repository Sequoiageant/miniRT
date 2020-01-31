/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:06:04 by julnolle          #+#    #+#             */
/*   Updated: 2019/11/15 13:58:16 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_size(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen((char *)s1) - 1;
	while (s1[start] && is_charset(s1[start], set))
		start++;
	while (is_charset(s1[end], set) && (ft_strlen((char *)s1) - start > 0))
		end--;
	return (end + 1 - start);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[i] && is_charset(s1[i], set))
		i++;
	size = get_size(s1, set);
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	j = 0;
	if (size > 0)
		while (j < size)
		{
			str[j] = s1[i];
			i++;
			j++;
		}
	str[j] = '\0';
	return (str);
}
