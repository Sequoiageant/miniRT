/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/12 18:50:32 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <mlx.h>
# include <stdio.h> //<====== A ENLEVER
# include "libft.h"
# include "get_next_line.h"

/*
** --------------------------------- Defines ---------------------------------
*/

# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0

# define NB_STATE	3
# define NB_OBJ		6

# define SP			"sp"
# define PL			"pl"
# define SQ			"sq"
# define CY			"cy"
# define TR			"tr"
# define R			"r"
# define A			"a"
# define C			"c"
# define L			"l"

/*
** ----------------------------------- Enum ----------------------------------
*/

enum			e_bool
{
	false,
	true
};

enum			e_state
{
	ENV,
	OBJECT,
	ERROR
};

enum			e_obj
{
	SPHERE,
	PLANE,
	SQUARE,
	CYLINDER,
	TRIANGLE,
	NO_OBJ
};

/*
** -------------------------------- Structures -------------------------------
*/

typedef struct		s_state_machine
{
	enum e_state	state;	

}					t_stm;

/*
** <============< graphics structures >============>
*/

/*
** mlibx structure
*/

typedef struct		s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}					t_data;

/*
** image structure <== to be deleted ??
*/

typedef struct		s_image {
	int		test;
}					t_image;

/*
** window structure
*/

typedef struct		s_win
{
	double		w;
	double		h;
	enum e_bool	set;
}					t_win;

/*
** <============< utilitary structures >============>
*/

/*
** vector structure
*/

typedef struct		s_vector3d
{
	double x;
	double y;
	double z;
}					t_vec3;

/*
** color structure
*/

typedef struct		s_color
{
	int r;
	int g;
	int b;
	int t;
}					t_col;

/*
** <===========< environment structures >===========>
*/

/*
** ambiant light structure
*/

typedef struct		s_ambiant_light
{
	double	lum;
	t_col	color;
}					t_ambl;

/*
** light structure
*/

typedef struct		s_light
{
	double	lum;
	t_vec3	pos;
	t_col	color;
}					t_light;

/*
** camera structure
*/

typedef struct		s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	int		fov;
}					t_cam;

/*
** <=============< objects structures >=============>
*/

/*
** sphere structure
*/

typedef struct		s_sphere
{
	t_vec3	pos;
	double	dia;
	t_col	color;
}					t_sp;

/*
** plane structure
*/

typedef struct		s_plane
{
	t_vec3	pos;
	t_vec3	dir;
	t_col	color;
}					t_pl;

/*
** plane structure
*/

typedef struct		s_square
{
	t_vec3	pos;
	double	h;
	t_vec3	dir;
	t_col	color;
}					t_sq;

/*
** cylindre structure
*/

typedef struct		s_cylindre
{
	t_vec3	pos;
	double	h;
	double	dia;
	t_vec3	dir;
	t_col	color;
}					t_cy;

/*
** triangle structure
*/

typedef struct		s_triangle
{
	t_vec3	pos1;
	t_vec3	pos2;
	t_vec3	pos3;
	t_col	color;
}					t_tr;

typedef struct		s_object
{
	char		*type;
	union
	{
		t_sp		sp;
		t_pl		pl;
		t_sq		sq;
		t_cy		cy;
		t_tr		tr;
		enum e_bool	err;
	}				u_obj;
	struct s_object	*next;
}					t_obj;

/*
** ------------------------------- Environment ------------------------------
*/
typedef	int			(*t_func)(t_win *, char *);
void				ft_set_win(char **tab, t_win *win);
void				ft_set_ambiant_light(char **tab);
void				ft_set_camera(char **tab);
void				ft_set_sphere(char **tab);

/*
** --------------------------------- Vectors --------------------------------
*/

float				ft_dot_product(float *u, float *v, int dim);
void				ft_cross_product(float *u, float *v, float *p);
void				ft_add_vec(float *u, float *v, float *p, int dim);
void				ft_sub_vec(float *u, float *v, float *p, int dim);
float				ft_norm_vec(float *u, int dim);
void				ft_normalize(float *vec, int dim);
float				ft_norm_vec2(float *vec, int dim);
float				*ft_get_normalize(float *vec, int dim);
float				*ft_mult_vec3(float *u, float m);

/*
** ---------------------------------- Utils ---------------------------------
*/

void				ft_pixel_put(t_data *data, int x, int y, int color);
int					create_trgb(int t, int r, int g, int b);
double				ft_atof(const char *str);

/*
** ---------------------------------- forms ---------------------------------
*/

void				ft_draw_circle(t_data *data);
void				ft_draw_square(t_data *data);
void				ft_draw_triangle(t_data *data);
void				ft_draw_sphere(t_data *data);
void				ft_draw_hex(t_data *data);

/*
** ------------------------------- Ray tracing ------------------------------
*/

void				ft_raytracing(t_data *data, t_win *win);

#endif
