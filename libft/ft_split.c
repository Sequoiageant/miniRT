/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:23:00 by julien            #+#    #+#             */
/*   Updated: 2020/04/30 15:22:23 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_store_word(char const *src, size_t *i, char c)
{
	char	*dest;
	size_t	j;
	size_t	len;

	j = *i;
	len = 0;
	while (src[j] != c && src[j] != '\0')
	{
		j++;
		len++;
	}
	dest = NULL;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest)
	{
		j = 0;
		while (src[*i] != 0 && src[*i] != c)
		{
			dest[j] = src[*i];
			(*i)++;
			j++;
		}
		dest[j] = '\0';
	}
	return (dest);
}

static size_t	count_words(char const *str, char c)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			count++;
		i++;
	}
	if (str[0] != c)
		count++;
	return (count);
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

char			**ft_split(char const *str, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;

	tab = NULL;
	tab = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (tab)
	{
		i = 0;
		j = 0;
		while (str[i] != 0)
		{
			if (str[i] == c)
				i++;
			else
			{
				if (!(tab[j] = ft_store_word(str, &i, c)))
					return (ft_free_split(&tab, i));
				j++;
			}
		}
		tab[j] = NULL;
	}
	return (tab);
}
