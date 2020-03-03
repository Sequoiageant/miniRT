/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:40:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/03 13:44:52 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bmp.h"

struct rgb_data {
	float r, g, b;
};

int fill_file()
{
	int width = 400;
	int height = 400;
	t_col pixels[width*height];

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int a = y * width + x;

			if ((x > 50 && x < 350) && (y > 50 && y < 350)) {
				pixels[a].r = 255;
				pixels[a].g = 255;
				pixels[a].b = 5;
			} else {
				pixels[a].r = 55;
				pixels[a].g = 55;
				pixels[a].b = 55;
			}
		}
	}
	return (0);
}

int	main(void)
{
	int fd;
	char *name = ft_strjoin(BMP_LOCATION, "test");
	if (name)
	{
		if ((fd = open(name, O_WRONLY | O_CREAT, OPEN_FLAG)) != -1)
		{
			write (fd, "ca marche", ft_strlen("ca marche"));
			printf("Saved to : %s\n", name);
			fill_file();
		}
		free(name);
	}
	return (0);
}
