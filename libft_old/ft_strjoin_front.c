/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:28:10 by julnolle          #+#    #+#             */
/*   Updated: 2019/12/18 18:47:03 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strjoin_front(char *front, char **src)
{
	char *tmp;

	if (front == NULL || *src == NULL)
		return ;
	tmp = ft_strdup(*src);
	free(*src);
	*src = ft_strjoin(front, tmp);
	free(tmp);
}
