/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:05:51 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/24 19:10:23 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
	}
	return (count);
}

static int		ft_count_size(char const *s, char c)
{
	int	size;

	size = 0;
	while (s[size] != c && s[size])
	{
		size++;
	}
	return (size);
}

static char		*ft_newstr(const char *s1, int size, char c)
{
	char	*dst;
	int		i;

	i = 0;
	if (!(dst = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (*s1 && i < size && *s1 != c)
	{
		dst[i] = (char)*s1;
		s1++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char		**ft_free_split(char ***tab, size_t stop)
{
	size_t i;

	i = 0;
	if (stop > 0)
		stop--;
	while (i < stop)
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		size;
	int		words;

	i = 0;
	if (s == NULL)
		return (NULL);
	words = ft_count_words(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (*s && words--)
	{
		while (*s == c)
			s++;
		size = ft_count_size(s, c);
		if (!(tab[i] = ft_newstr(s, size, c)))
			return (ft_free_split(&tab, i));
		while (*s && *s != c)
			s++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
