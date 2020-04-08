/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 18:32:24 by julien            #+#    #+#             */
/*   Updated: 2020/04/07 19:40:12 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_error(int error, size_t line_nb)
{
	const char *str_error[] = {SAVE_ERROR, ARGS_ERROR, FD_ERROR,
		VECTOR_ERROR, TYPE_ERROR, ENV_ERROR,
		SIGN_ERROR, INT_ERROR, COL_ERROR,
		RANGE_ERROR, RANGE2_ERROR, FOV_ERROR,
		PROP_ERROR, MALLOC_ERROR
	};
	size_t		i;
	size_t		nb_error;

	i = 0;
	nb_error = sizeof(str_error) / sizeof(str_error[0]);
	while (i < nb_error)
	{
		if (error & (1 << i))
			print_error(str_error[i], line_nb);
		i++;
	}
}

int		ft_strnequ(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		split_size_error(char **tab, size_t size, int *error)
{
	size_t i;

	i = 0;
	while (tab[i] != 0)
		i++;
	if (size == i)
		return (TRUE);
	else
		*error |= PROP_ERROR_MASK;
	return (FALSE);
}

void	free_split(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	init_data(t_data *data)
{
	data->objlst_set = FALSE;
	data->cams_set = FALSE;
	data->lights_set = FALSE;
}

/*void	ft_free_tab2(char ***tab)
{
	int i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = NULL;
}*/