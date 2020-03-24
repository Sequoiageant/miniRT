/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:23:00 by julien            #+#    #+#             */
/*   Updated: 2020/03/24 19:24:42 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static char		*ft_store_word(char const *str, size_t *i)
{
	char	*dest;
	size_t	j;
	size_t	len;

	j = *i;
	len = 0;
	while (!is_space(str[j]) && str[j] != '\0')
	{
		j++;
		len++;
	}
	dest = NULL;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest)
	{
		j = 0;
		while (str[*i] != 0 && !is_space(str[*i]))
		{
			dest[j] = str[*i];
			(*i)++;
			j++;
		}
		dest[j] = '\0';
	}
	return (dest);
}

static size_t	count_words(char const *str)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (is_space(str[i]) && !is_space(str[i + 1])
			&& str[i + 1] != 0)
			count++;
		i++;
	}
	if (!is_space(str[0]))
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

char	**ft_split_whitespaces(char const *str)
{
	char	**tab;
	size_t	i;
	size_t	j;

	tab = NULL;
	tab = malloc(sizeof(char *) * (count_words(str) + 1));
	if (tab)
	{
		i = 0;
		j = 0;
		while (str[i] != 0)
		{
			if (is_space(str[i]))
				i++;
			else
			{
				if (!(tab[j] = ft_store_word(str, &i)))
					return (ft_free_split(&tab, i));
				j++;
			}
		}
		tab[j] = NULL;
	}
	return (tab);
}
