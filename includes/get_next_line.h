/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:47:17 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/06 17:14:53 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32

# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *src);
int		get_next_line(int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
