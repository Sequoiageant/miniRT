/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/23 19:03:30 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <mlx.h>
# include <limits.h>
# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"

/*
** --------------------------------- Defines ---------------------------------
*/

# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0

# define MACHINE_ERROR		-1
# define MACHINE_CONTINUE	1
# define MACHINE_AGAIN		0

# define NB_STATE	4
# define NB_OBJ		5
# define NB_ENV		4

# define EPSILON	1.0e-6
# define BIAS		1.0e-3
# define LARGE_NUMB	1.0e99
# define PI			3.1415927

# define P_R		"R"
# define P_A		"A"
# define P_C		"c"
# define P_L		"l"
# define P_SP		"sp"
# define P_PL		"pl"
# define P_SQ		"sq"
# define P_CY		"cy"
# define P_TR		"tr"

# define STR_ENV	"RAcl"

# define SP			0x000001
# define PL			0x000002
# define SQ			0x000004
# define CY			0x000008
# define TR			0x000010


# ifdef LINUX
/*
** Keycodes and screen size LINUX
*/
#  define MAX_W		1920
#  define MAX_H		1080

#  define ESC		65307
#  define LEFT		65361
#  define RIGHT		65363

#  else
/*
** Keycodes and screen size MAC 42
*/

#  define MAX_W		2560
#  define MAX_H		1440

#  define ESC		53
#  define LEFT		123
#  define RIGHT		124
#  define UP		126
#  define DOWN		125
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define KEY_W		13
#  define KEY_Q		12
#  define KEY_E		14
#  define KEY_J		38
#  define KEY_K		40
#  define KEY_L		37
#  define KEY_I		34
#  define KEY_U		32
#  define KEY_O		31
#  define KEY_SPACE	49
#  define KEY_PLUS	69
#  define KEY_MINUS	78

# endif

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
	EMPTY,
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
	TRIANGLE
};

/*
** -------------------------------- Structures -------------------------------
*/

typedef struct		s_state_machine
{
	enum e_state	state;
	int				obj;
}					t_stm;

/*
** <============< graphics structures >============>
*/

/*
** mlibx structure
*/

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	pad[4];
}					t_mlx;

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
	int			w;
	int			h;	
	double		x;
	double		y;
	enum e_bool	set;
	char		pad[4];
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
** quadratic equation structure
*/

typedef struct		s_quadra
{
	double a;
	double b;
	double c;
	double delta;
	double t;
	double t1;
	double t2;
}					t_quadra;

/*
** intersection structure
*/

typedef struct		s_intersection
{
	enum e_bool	set;
	double		t;
	double		min_t;
	t_vec3		pos;
	t_vec3		normal;
	t_vec3		origin;
	t_col		col;
}					t_inter;

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
	double			lum;
	t_vec3			pos;
	t_col			color;
	struct s_light	*next;
}					t_light;

/*
** camera structure
*/

typedef struct		s_camera
{
	int				nbr;	
	t_vec3			pos;
	t_vec3			dir;
	double			fov;
	struct s_camera	*next;
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
	t_vec3	normal;
	t_col	color;
}					t_pl;

/*
** plane structure
*/

typedef struct		s_square
{
	t_vec3	p0;
	t_vec3	dir;
	double	h;
	t_col	color;
}					t_sq;

/*
** cylindre structure
*/

typedef struct		s_cylindre
{
	t_vec3	pos;
	t_vec3	dir;
	t_col	color;
	double	dia;
	double	h;
}					t_cy;

/*
** triangle structure
*/

typedef struct		s_triangle
{
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	p3;
	t_col	color;
}					t_tr;

/*
** objects linked list
*/

typedef struct		s_object
{
	enum e_obj		type;
	int				num;
	t_col			col;
	union
	{
		t_sp		sp;
		t_pl		pl;
		t_sq		sq;
		t_cy		cy;
		t_tr		tr;
	}				u_obj;
	struct s_object	*next;
}					t_obj;

/*
** All environment + objects structure
*/

typedef struct		s_data
{
	t_cam	*cams;
	t_obj	*objlst;
	t_light	*lights;
	t_win	win;
	t_mlx	mlx;
	t_ambl	al;
	int		cam_num;
	char	pad[4];
}					t_data;

/*
** ------------------------------- Environment ------------------------------
*/

typedef	int			(*t_func)(t_data *, char **, t_stm *);
typedef	int			(*t_func2)(char **, t_obj **, t_data *, int);
typedef	int			(*t_func3)(char **, t_data *);
typedef	int			(*t_ray)(t_vec3 *, t_obj *, t_inter *);
int					set_res(char **tab, t_data *data);
int					set_light(char **tab, t_data *data);
int					set_al(char **tab, t_data *data);
int					set_cam(char **tab, t_data *data);
int					set_sp(char **tab, t_obj **objlst, t_data *data, int num);
int					set_sq(char **tab, t_obj **objlst, t_data *data, int num);
int					set_pl(char **tab, t_obj **objlst, t_data *data, int num);
int					set_cy(char **tab, t_obj **objlst, t_data *data, int num);
int					set_tr(char **tab, t_obj **objlst, t_data *data, int num);

/*
** --------------------------------- Vectors --------------------------------
*/

t_vec3				new_vec(double a, double b, double c);
void				reset_vec(t_vec3 *vec);
t_vec3				new_vec_from_char(char *a, char *b, char *c);
double				ft_dot_product3(t_vec3 u, t_vec3 v);
t_vec3				ft_cross_product3(t_vec3 *u, t_vec3 *v);
t_vec3				ft_add_vec3(t_vec3 u, t_vec3 v);
t_vec3				ft_sub_vec3(t_vec3 u, t_vec3 v);
double				ft_norm_vec3(t_vec3 *u);
void				ft_normalize(t_vec3 *vec);
double				ft_norm_vec3_2(t_vec3 *vec);
t_vec3				ft_get_normalized(t_vec3 vec);
double				*ft_mult_vec3(t_vec3 *u, t_vec3 m);
t_vec3				ft_multby_vec3(t_vec3 *u, double mult);
t_vec3				ft_divby_vec3(t_vec3 *u, double div);
t_vec3				ft_decal_vec3(t_vec3 *u, double sub);
void				ft_rot_vec3(t_vec3 *u, t_vec3 *dir);
void   				rot_3d(t_vec3 *v, double rot);

/*
** ------------------------------ Intersections -----------------------------
*/

int					rt_sp(t_vec3 *ray, t_obj *objlst, t_inter *inter);
int					rt_pl(t_vec3 *ray, t_obj *objlst, t_inter *inter);
int					rt_tr(t_vec3 *ray, t_obj *objlst, t_inter *inter);
int					rt_sq(t_vec3 *ray, t_obj *objlst, t_inter *inter);
int					rt_cy(t_vec3 *ray, t_obj *objlst, t_inter *inter);

/*
** ---------------------------------- Utils ---------------------------------
*/

int					ft_launch_window(t_data *data);
void				ft_pixel_put(t_mlx *mlx, int x, int y, int color);
int					rgb_to_int(int r, int g, int b);
void				ft_free_tab2(char **tab);
double 				ft_max(double a, double b);
double 				ft_min(double a, double b);
int					ft_close(t_data *data);
double				deg_to_rad(double alpha);
double				rad_to_deg(double alpha);
double				normalize_and_markout(double to_mod, double denom);

/*
** ---------------------------------- Colors ---------------------------------
*/

t_col				char_to_col(char *r, char *g, char *b);
int					color_encode(t_col col);
t_col				mult_col_double(t_col col, double mult);
t_col				add_colors(t_col col, t_col add);
t_col				sub_colors(t_col col, t_col sub);
t_col				mult_col(t_col col1, t_col col2);
t_col				ft_min_col(t_col col);
void				init_color(t_col *col);

/*
** ---------------------------------- forms ---------------------------------
*/

void				ft_draw_circle(t_mlx *mlx);
void				ft_draw_square(t_mlx *mlx);
void				ft_draw_triangle(t_mlx *mlx);
void				ft_draw_sphere(t_mlx *mlx);
void				ft_draw_hex(t_mlx *mlx);

/*
** ------------------------------- Ray tracing ------------------------------
*/

void				ft_raytracing(t_data *data);

#endif
