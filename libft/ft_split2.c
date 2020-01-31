/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:22:53 by julnolle          #+#    #+#             */
/*   Updated: 2019/11/18 16:48:43 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_strlen2(char const *str, char c, size_t i)
{
	size_t j;
	size_t k;

	j = i;
	k = 0;
	while (str[j] != c && str[j] != '\0')
		if (str[j] == c)
			j++;
		else
		{
			k++;
			j++;
		}
	return (k);
}

static char		*ft_strdup2(char const *s, size_t *i, char c)
{
	size_t	j;
	size_t	size;
	char	*tab;

	size = ft_strlen2(s, c, *i);
	if (!(tab = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	j = 0;
	while (s[*i] != '\0' && s[*i] != c)
	{
		tab[j] = s[*i];
		(*i)++;
		j++;
	}
	tab[j] = '\0';
	return (tab);
}

static int		count_words(char const *s, char c)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (s[i] != 0)
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	if ((s[0]) != c)
		count++;
	return (count);
}

static int		ft_free_split(char ***tab, size_t stop)
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
	return (0);
}

char			**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**tab;

	tab = NULL;
	if (s != NULL)
	{
		if (!(tab = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1))))
			return (NULL);
		i = 0;
		j = 0;
		while (s[i] != 0)
		{
			if (s[i] == c)
				i++;
			else
			{
				if (!(tab[j] = ft_strdup2(s, &i, c)))
					ft_free_split(&tab, i);
				j++;
			}
		}
		tab[j] = NULL;
	}
	return (tab);
}
