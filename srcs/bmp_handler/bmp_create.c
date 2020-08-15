/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 18:35:40 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/01 16:26:37 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bmp.h"

static unsigned char	*file_header_bmp(int filesize)
{
	unsigned char	*bmpfileheader;

	if (!(bmpfileheader = (unsigned char*)malloc(14 * sizeof(unsigned char))))
		return (0);
	ft_bzero(bmpfileheader, 14);
	bmpfileheader[0] = 'B';
	bmpfileheader[1] = 'M';
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);
	bmpfileheader[10] = 54;
	return (bmpfileheader);
}

static unsigned char	*info_header_bmp(t_win res)
{
	unsigned char	*bmpinfoheader;

	if (!(bmpinfoheader = (unsigned char*)malloc(40 * sizeof(unsigned char))))
		return (0);
	ft_bzero(bmpinfoheader, 40);
	bmpinfoheader[0] = 40;
	bmpinfoheader[4] = (unsigned char)(res.w);
	bmpinfoheader[5] = (unsigned char)(res.w >> 8);
	bmpinfoheader[6] = (unsigned char)(res.w >> 16);
	bmpinfoheader[7] = (unsigned char)(res.w >> 24);
	bmpinfoheader[8] = (unsigned char)(res.h);
	bmpinfoheader[9] = (unsigned char)(res.h >> 8);
	bmpinfoheader[10] = (unsigned char)(res.h >> 16);
	bmpinfoheader[11] = (unsigned char)(res.h >> 24);
	bmpinfoheader[12] = 1;
	bmpinfoheader[14] = 32;
	return (bmpinfoheader);
}

static int				write_img(int fd, const unsigned char *img, t_win res)
{
	int line;

	line = res.h - 1;
	while (line >= 0)
	{
		if (write(fd, img + res.w * line * 4, res.w * 4) == FAILURE)
			return (FAILURE);
		line--;
	}
	return (SUCCESS);
}

int						save_bmp(const unsigned char *img, const t_win res)
{
	int				fd;
	unsigned char	*bmpfileheader;
	unsigned char	*bmpinfoheader;
	char			*name;
	char			*time_stamp;

	name = ft_strjoin(BMP_LOCATION, "minirt_");
	time_stamp = ft_itoa(time(NULL));
	ft_strjoin_back(time_stamp, &name);
	free(time_stamp);
	ft_strjoin_back(".bmp", &name);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	free(name);
	bmpfileheader = file_header_bmp(14 + 40 + 3 * res.w * res.h);
	write(fd, bmpfileheader, 14);
	free(bmpfileheader);
	bmpinfoheader = info_header_bmp(res);
	write(fd, bmpinfoheader, 40);
	free(bmpinfoheader);
	if (write_img(fd, img, res) == FAILURE)
		return (FAILURE);
	close(fd);
	return (SUCCESS);
}
