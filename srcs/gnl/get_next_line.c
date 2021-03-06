/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:51:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/13 19:04:17 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	ft_strjoin_back(char *back, char **src)
{
	char *tmp;

	if (back == NULL || *src == NULL)
		return ;
	tmp = ft_strdup(*src);
	free(*src);
	*src = NULL;
	*src = ft_strjoin(tmp, back);
	free(tmp);
	tmp = NULL;
}

static	int		ft_strchr_pos(const char *s, int c)
{
	size_t pos;

	pos = 0;
	while (*s != c)
	{
		if (*s == '\0')
			return (-1);
		s++;
		pos++;
	}
	return (pos);
}

static	int		ft_read_line(char **str, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;

	ret = 1;
	while (ft_strchr_pos(*str, '\n') == -1 && ret > 0)
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
		{
			buf[ret] = '\0';
			ft_strjoin_back(buf, str);
		}
	}
	return (ret);
}

static	int		ft_fill_line(char **line, char **str)
{
	ssize_t	pos;
	char	*tmp;

	pos = 0;
	if ((pos = ft_strchr_pos(*str, '\n')) != -1)
	{
		*line = ft_substr(*str, 0, pos);
		tmp = ft_strdup(*str);
		free(*str);
		*str = NULL;
		*str = ft_strdup(tmp + pos + 1);
		free(tmp);
		tmp = NULL;
		return (1);
	}
	else
	{
		*line = *str;
		return (0);
	}
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	static char	*str;
	int			ret;

	ret = -1;
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (!str)
	{
		str = (char *)malloc(sizeof(char) * 1);
		str[0] = '\0';
	}
	if (str)
	{
		ret = ft_read_line(&str, fd);
		if (ret != -1)
			ret = ft_fill_line(line, &str);
	}
	return (ret);
}
