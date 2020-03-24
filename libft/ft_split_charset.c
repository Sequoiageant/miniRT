/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:23:00 by julien            #+#    #+#             */
/*   Updated: 2020/03/24 18:50:16 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_charset(char c, char *charset)
{
	size_t i;

	i = 0;
	while (charset[i] != 0)
	{
		if (charset[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static char		*ft_store_word(char *src, size_t *i, char *charset)
{
	char	*dest;
	size_t	j;
	size_t	len;

	j = *i;
	len = 0;
	while (!is_charset(src[j], charset) && src[j] != '\0')
	{
		j++;
		len++;
	}
	dest = NULL;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest)
	{
		j = 0;
		while (src[*i] != 0 && !is_charset(src[*i], charset))
		{
			dest[j] = src[*i];
			(*i)++;
			j++;
		}
		dest[j] = '\0';
	}
	return (dest);
}

static size_t	count_words(char *str, char *charset)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (is_charset(str[i], charset) && !is_charset(str[i + 1], charset)
			&& str[i + 1] != 0)
			count++;
		i++;
	}
	if (!is_charset(str[0], charset))
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

char	**ft_split_charset(char *str, char *charset)
{
	char	**tab;
	size_t	i;
	size_t	j;

	tab = NULL;
	tab = malloc(sizeof(char *) * (count_words(str, charset) + 1));
	if (tab)
	{
		i = 0;
		j = 0;
		while (str[i] != 0)
		{
			if (is_charset(str[i], charset))
				i++;
			else
			{
				if (!(tab[j] = ft_store_word(str, &i, charset)))
					return (ft_free_split(&tab, i));
				j++;
			}
		}
		tab[j] = NULL;
	}
	return (tab);
}
