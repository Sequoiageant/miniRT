/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:34:04 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/08 16:51:53 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <time.h>

# ifndef BMP_LOCATION
#  define BMP_LOCATION "./bmp_saved/"
# endif

# ifndef OPEN_FLAG
#  define OPEN_FLAG S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# endif

typedef struct			s_header
{
	char	type[2];
	int		reserved;
	int		file_size;
	int		offset;
}						t_header;

typedef struct			s_infos
{
	int		header_size;
	int		image_size;
	int		nb_color;
	int		important_color;
	int		compression;
	int		width;
	int		height;
	int		x_res;
	int		y_res;
	short	panes;
	short	bpp;
}						t_infos;

#endif
