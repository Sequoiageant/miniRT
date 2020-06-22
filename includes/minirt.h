/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 19:40:47 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/22 14:38:47 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

/*
** --------------------------------- Defines ---------------------------------
*/

# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0

/*
** Some Constants
*/

# define EPSILON	1.0e-6
# define BIAS		1.0e-3
# define LARGE_NUMB	1.0e99
# define PI			3.1415927

/*
** Errors
*/

# define SAVE_ERROR		"Use '-save' as 2nd arg to save image as [.bmp]."
# define ARGS_ERROR		"2 args max\nUse '-save' as 2nd arg to make [.bmp]."
# define FD_ERROR		"The path to configuration file must be valid."
# define VECTOR_ERROR	"One or more vector(s), position or dir. is not valid"
# define TYPE_ERROR		"Unidentified Type in configuration file."
# define ENV_ERROR		"The R & A must be unique properties."
# define SIGN_ERROR		"The value must be positive int or float."
# define INT_ERROR		"The value must be of positive int"
# define COL_ERROR		"A color is defined by three ints in range [0; 255]."
# define RANGE_ERROR	"The value must be in the range [0.0; 1.0]"
# define RANGE2_ERROR	"The normal vector must be in the range [-1.0; 1.0]"
# define FOV_ERROR		"The FOV must be in the range [0; 180]"
# define PROP_ERROR		"Incorrect number of properties."
# define TYPE_NB_ERROR	"One type of properties is missing"
# define MALLOC_ERROR	"Malloc error."
# define BMP_SUCCESS	"Screenshot saved in ./bmp_saved/\n"

# define SAVE_ERROR_MASK	0x000001
# define ARGS_ERROR_MASK	0x000002
# define FD_ERROR_MASK		0x000004
# define VECTOR_ERROR_MASK	0x000008
# define TYPE_ERROR_MASK	0x000010
# define ENV_ERROR_MASK		0x000020
# define SIGN_ERROR_MASK	0x000040
# define INT_ERROR_MASK		0x000080
# define COL_ERROR_MASK		0x000100
# define RANGE_ERROR_MASK	0x000200
# define RANGE2_ERROR_MASK	0x000400
# define FOV_ERROR_MASK		0x000800
# define PROP_ERROR_MASK	0x001000
# define TYPE_NB_ERROR_MASK	0x002000
# define MALLOC_ERROR_MASK	0x004000

/*
** Finite State Machine
*/

# define NB_STATE	4
# define NB_OBJ		5
# define NB_ENV		4

# define MACHINE_ERROR		-1
# define MACHINE_CONTINUE	1
# define MACHINE_AGAIN		0

# define P_R		"R"
# define P_A		"A"
# define P_C		"c"
# define P_L		"l"
# define P_SP		"sp"
# define P_PL		"pl"
# define P_SQ		"sq"
# define P_CY		"cy"
# define P_TR		"tr"

# define S_R		3
# define S_A		3
# define S_C		4
# define S_L		4
# define S_SP		4
# define S_PL		4
# define S_SQ		5
# define S_CY		6
# define S_TR		5

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
#  define KEY_S		115

# else

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
	int				error;
	short			res_set;
	short			al_set;
}					t_stm;

/*
** <============< graphics structures >============>
*/

/*
** mlibx structure
*/

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*mlx_win;
	int				max_w;
	int				max_h;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				end;
	char			pad[4];
}					t_mlx;

/*
** window structure
*/

typedef struct		s_win
{
	int			w;
	int			h;
	double		x;
	double		y;
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

typedef struct		s_matrix
{
	double d[4][4];
}					t_matrix;

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
	double		t;
	double		min_t;
	t_vec3		pos;
	t_vec3		normal;
	t_vec3		origin;
	t_col		col;
	enum e_bool	set;
	char		pad[4];
}					t_inter;

/*
** truncature structure
*/

typedef struct		s_truncature
{
	double t;
	double tin;
	double tout;
}					t_trunc;

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
	char			pad[4];
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
	short	cam_num;
	short	objlst_set;
	short	cams_set;
	short	lights_set;
}					t_data;

/*
** ------------------------------- MLX Events -------------------------------
*/

int					launch_window(t_data *data);
int					save_image(t_data *data);
int					key_event(int key, t_data *data);
int					ft_close(t_data *data);
void				free_minirt(t_data *data);

/*
** --------------------------------- Camera ---------------------------------
*/

int					choose_cam(int key, t_data *data);
t_cam				select_cam(t_data data);
t_matrix			look_at(t_vec3 origin, t_vec3 dir);
t_vec3				multiply_by_matrix(t_vec3 p, t_matrix m);

/*
** --------------------------------- Parser ---------------------------------
*/

int					run_machine(char *line, t_data *data, t_stm *machine);
int					list_objects(char **tab, t_data *data, int i);
int					is_int_or_float(char *str, char sign);
int					ckeck_vec(char *str);
int					set_vector(char *str, t_vec3 *vec, int *err);
int					set_normal_vec(char *str, t_vec3 *vec, int *err);
int					ckeck_col(char *str);
int					set_color(char *str, t_col *col, int *err);
int					set_if_in_rnge(char *s, double *d, double min, double max);
int					is_int(char *str, char sign);
int					is_in_range_col(t_col *col);
int					split_size_error(char **tab, size_t size, int *error);
void				init_data(t_data *data, t_stm *machine);
void				select_error(int error, size_t line_nb);

/*
** ------------------------------- Parser Env ------------------------------
*/

typedef	int			(*t_func)(t_data *, char **, t_stm *);
typedef	int			(*t_func2)(char **, t_obj **, t_data *, t_stm *);
typedef	int			(*t_func3)(char **, t_data *, t_stm *);
typedef	int			(*t_ray)(t_vec3 *, t_obj *, t_inter *);
int					set_res(char **tab, t_data *data, t_stm *machine);
int					set_light(char **tab, t_data *data, t_stm *machine);
int					set_al(char **tab, t_data *data, t_stm *machine);
int					set_cam(char **tab, t_data *data, t_stm *machine);

/*
** ----------------------------- Parser Objects ----------------------------
*/

int					set_sp(char **tab, t_obj **objlst, t_data *data, t_stm *m);
int					set_sq(char **tab, t_obj **objlst, t_data *data, t_stm *m);
int					set_pl(char **tab, t_obj **objlst, t_data *data, t_stm *m);
int					set_cy(char **tab, t_obj **objlst, t_data *data, t_stm *m);
int					set_tr(char **tab, t_obj **objlst, t_data *data, t_stm *m);
void				ft_add_sp(t_obj **objlst, t_sp sp, t_data *data);
void				ft_add_sq(t_obj **objlst, t_sq sq, t_data *data);
void				ft_add_pl(t_obj **objlst, t_pl pl, t_data *data);
void				ft_add_cy(t_obj **objlst, t_cy cy, t_data *data);
void				ft_add_tr(t_obj **objlst, t_tr tr, t_data *data);

/*
** --------------------------------- Vectors --------------------------------
*/

t_vec3				new_vec(double a, double b, double c);
void				reset_vec(t_vec3 *vec);
t_vec3				new_vec_from_char(char *a, char *b, char *c);
double				dot_product3(t_vec3 u, t_vec3 v);
t_vec3				cross_product3(t_vec3 *u, t_vec3 *v);
t_vec3				add_vec3(t_vec3 u, t_vec3 v);
t_vec3				sub_vec3(t_vec3 u, t_vec3 v);
double				norm_vec3(t_vec3 *u);
void				ft_normalize(t_vec3 *vec);
double				norm_vec3_2(t_vec3 *vec);
t_vec3				get_normalized(t_vec3 vec);
t_vec3				multby_vec3(t_vec3 *u, double mult);

/*
** ------------------------------ Intersections -----------------------------
*/

int					rt_sp(t_vec3 *ray, t_obj *objlst, t_inter *inter);
int					rt_pl(t_vec3 *ray, t_obj *objlst, t_inter *inter);
int					rt_tr(t_vec3 *ray, t_obj *objlst, t_inter *inter);
int					rt_sq(t_vec3 *ray, t_obj *objlst, t_inter *inter);
int					rt_cy(t_vec3 *ray, t_obj *objlst, t_inter *inter);
t_vec3				sign_normal(t_vec3 normal, t_vec3 ori, t_vec3 pos);

/*
** ---------------------------------- Utils ---------------------------------
*/
int					ft_strnequ(char *s1, char *s2, int n);
void				ft_pixel_put(t_mlx *mlx, int x, int y, int color);
int					rgb_to_int(int r, int g, int b);
void				ft_free_tab2(char ***tab);
void				free_split(char **tab);
double				ft_max(double a, double b);
double				ft_min(double a, double b);
double				deg_to_rad(double alpha);
double				rad_to_deg(double alpha);
double				normalize_and_markout(double to_mod, double denom);
int					print_error(const char *error, int line_nb);
int					check_missing_type(t_data *data, t_stm *m, size_t *line);
void				reset_inter(t_inter *inter);
t_vec3				trace_ray_normalized(t_win win, t_cam camera);
int					solve_quadratic(t_quadra *q);

/*
** ---------------------------------- Colors ---------------------------------
*/

t_col				char_to_col(char *r, char *g, char *b);
t_col				int_to_col(int r, int g, int b);
int					color_encode(t_col col);
void				init_color(t_col *col);
t_col				mult_col_double(t_col col, double mult);
t_col				add_colors(t_col col, t_col add);
t_col				sub_colors(t_col col, t_col sub);
t_col				mult_col(t_col col1, t_col col2);
t_col				ft_min_col(t_col col);

/*
** ------------------------------- Ray tracing ------------------------------
*/

void				raytracing(t_data *data);
void				reset_image(t_data *data);

/*
** ------------------------------- bmp Handler ------------------------------
*/

int					save_bmp(const unsigned char *data, const t_win res);

/*
** ---------------------------- Debug (debug.c) -----------------------------
*/

#endif
