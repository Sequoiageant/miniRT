/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:02:42 by julnolle          #+#    #+#             */
/*   Updated: 2020/08/14 18:27:20 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define SUCCESS	0
# define FAILURE	-1
# define AGAIN		1
# define TRUE		1
# define FALSE		0

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int				ft_atoi(const char *str);
char			*ft_itoa(int n);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_isblank(int c);
int				ft_isupper(int c);
int				ft_islower(int c);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
int				ft_putchar(char c);
int				ft_putchar_fd(char c, int fd);
int				ft_putendl(char const *s);
int				ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
int				ft_putstr(char const *s);
int				ft_putstr_fd(char const *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *src);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *str);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
				size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);

/*
** my functions
*/
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
int				ft_lstsize(t_list *lst);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *));
t_list			*tab_to_list(char **tab);

/*
** my functions
*/
void			ft_putnbr_base(int nbr, char *base);
void			ft_put_revstr(char *str);
size_t			ft_nbrsize(long n);
size_t			ft_nbrsize_base(int n, int base_len);
void			ft_strjoin_back(char *back, char **src);
void			ft_strjoin_front(char *front, char **src);
char			*ft_itoa_base(long nb, char *base);
int				ft_strcmp(const char *s1, const char *s2);
double			ft_atof(const char *str);
char			**ft_split_charset(char const *str, char *charset);
char			**ft_split_whitespaces(char const *str);
void			free_tab_str(char **tab);
int				print_tab_str(char **tab);

#endif
