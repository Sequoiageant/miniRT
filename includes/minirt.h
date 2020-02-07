/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/07 17:46:30 by julnolle         ###   ########.fr       */
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
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>

/*
** --------------------------------- Defines ---------------------------------
*/
 
# define PI 3.1415926535
# define ABS(x) x < 0 ? -x : x

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
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_image {
}				t_image;

/*
** window structure
*/

typedef struct	s_win
{
	float	w;
	float	h;
	t_bool	set;
}				t_win;

/*
** vector structure
*/

typedef struct	s_vec
{
	float x;
	float y;
	float z;
}				t_vec;

/*
** ambiant light structure
*/

typedef struct	s_amb_light
{
	double	lum;
	int		r;
	int		g;
	int		b;
}				t_ambl;

/*
** light structure
*/

typedef struct	s_light
{
	double	x;
	double	y;
	double	z;	
	double	lum;
	int		r;
	int		g;
	int		b;
}				t_light;

/*
** camera structure
*/

typedef struct	s_camera
{
	double	x;
	double	y;
	double	z;	
	double	or_x;
	double	or_y;
	double	or_z;
	int		fov;
}				t_cam;

/*
** sphere structure
*/

typedef struct	s_sp
{
	double	x;
	double	y;
	double	z;
	double	dia;
	int		r;
	int		g;
	int		b;
}				t_sp;

/*
** ------------------------------- Environment ------------------------------
*/

void	ft_set_win(char **tab, t_win *win);
void	ft_set_ambiant_light(char **tab);
void	ft_set_camera(char **tab);
void	ft_set_sphere(char **tab);

/*
** --------------------------------- Vectors --------------------------------
*/

float	ft_dot_product(float *u, float *v, int dim);
void	ft_cross_product(float *u, float *v, float *p);
void	ft_add_vec(float *u, float *v, float *p, int dim);
void	ft_sub_vec(float *u, float *v, float *p, int dim);
float	ft_norm_vec(float *u, int dim);
void	ft_normalize(float *vec, int dim);
float	ft_norm_vec2(float *vec, int dim);

/*
** ---------------------------------- Utils ---------------------------------
*/

void	ft_putendl(char *s);
int		ft_atoi2(char **str);
void	ft_pixel_put(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
double	ft_atof(const char *str);

/*
** ---------------------------------- forms ---------------------------------
*/

void	ft_draw_circle(t_data *data);
void	ft_draw_square(t_data *data);
void	ft_draw_triangle(t_data *data);
void	ft_draw_sphere(t_data *data);
void	ft_draw_hex(t_data *data);

/*
** ------------------------------- Ray tracing ------------------------------
*/

void	ft_raytracing(t_data *data, t_win *win);

#endif
