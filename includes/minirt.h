/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/01/28 20:15:43 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <stdio.h>
#include "get_next_line.h"
/*
** --------------------------------- Defines ---------------------------------
*/

# define PI 3.1415926535

/*
** ----------------------------------- Enum ----------------------------------
*/

typedef enum	e_bool
{
	false = 0,
	true = 1
}				t_bool;

enum
{
	SPHERE, PLANE, CYLINDER, TRIANGLE, SQUARE
};

/*
** -------------------------------- Structures -------------------------------
*/

/*
** mlibx structure
*/

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
}				t_data;

/*
** window structure
*/

typedef struct	s_win
{
	int		x;
	int		y;
	t_bool	set;
}				t_win;

/*
** color structure <===== TO BE DELETED
*/

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
}				t_color;

/*
** ambiant light structure
*/

typedef struct	s_amb_light
{
	double	al_lum;
	int		al_lr;
	int		al_lg;
	int		al_lb;
}				t_amb_light;

/*
** light structure
*/

typedef struct	s_light
{
	double	li_x;
	double	li_y;
	double	li_z;	
	double	li_lum;
	int		lr;
	int		lg;
	int		lb;
}				t_light;

/*
** camera structure
*/

typedef struct	s_camera
{
	double	cam_x;
	double	cam_y;
	double	cam_z;	
	double	cam_or_x;
	double	cam_or_y;
	double	cam_or_z;
}				t_camera;

/*
** sphere structure
*/

typedef struct	s_sp
{
	double	sp_x;
	double	sp_y;
	double	sp_z;
	double	sp_dia;
	int		sp_r;
	int		sp_g;
	int		sp_b;
}				t_sp;

/*
** ---------------------------------- Utils ---------------------------------
*/

void	ft_putendl(char *s);
int		ft_atoi2(char **str);

#endif
