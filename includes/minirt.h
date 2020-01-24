/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/01/24 16:27:31 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <stdio.h>
#include "get_next_line.h"


typedef struct    data_s
{
	void          *mlx_ptr;
	void          *mlx_win;
}                 data_t;

void	ft_putendl(char *s);
int		ft_atoi(char **str);


#endif
