/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 15:52:08 by julien            #+#    #+#             */
/*   Updated: 2020/04/08 17:17:24 by julnolle         ###   ########.fr       */
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
	// bmpinfoheader[20] = (unsigned char)(imgsize);
	// bmpinfoheader[21] = (unsigned char)(imgsize >> 8);
	// bmpinfoheader[22] = (unsigned char)(imgsize >> 16);
	// bmpinfoheader[23] = (unsigned char)(imgsize >> 24);
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
	int				filesize;
	int				fd;
	unsigned char	*bmpfileheader;
	unsigned char	*bmpinfoheader;
	char			*name;

	name = ft_strjoin(BMP_LOCATION, "minirt_");
	ft_strjoin_back(ft_itoa(time(NULL)), &name);
	ft_strjoin_back(".bmp", &name);
	filesize = 14 + 40 + 3 * res.w * res.h;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0755);
	free(name);
	bmpfileheader = file_header_bmp(filesize);
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
