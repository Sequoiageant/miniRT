/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 19:16:50 by julien            #+#    #+#             */
/*   Updated: 2020/03/24 19:19:42 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int        main()
{
	char *strs;
	char **new;
	char *c;
	strs = " 	   je 				suis le test de split";
	c = " ";
	new = ft_split_whitespaces(strs);
	int i = 0;
	while (new[i] != 0)
	{
		printf("%s\n", new[i]);
		free(new[i]);
		new[i] = NULL;
		i++;
	}
	free(new);
	new = NULL;
	// printf("%zu\n", count_words(strs, c));
	return 0;
}
