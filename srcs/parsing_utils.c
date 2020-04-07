/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 18:32:24 by julien            #+#    #+#             */
/*   Updated: 2020/04/07 16:59:20 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_normal_vec(t_vec3 vec)
{
	return (vec.x >= -1.0 && vec.x <= 1.0
		&& vec.y >= -1.0 && vec.y <= 1.0
		&& vec.z >= -1.0 && vec.z <= 1.0);
}

int			set_if_in_rnge(char *s, double *d, double min, double max)
{
	*d = ft_atof(s);
	if (*d >= min && *d <= max)
		return (SUCCESS);
	return (FAILURE);
}

int			set_normal_vec(char *str, t_vec3 *vec, int *err)
{
	if (set_vector(str, vec, err) != FAILURE)
	{
		if (!is_normal_vec(*vec))
		{
			*err |= RANGE2_ERROR_MASK;
			return (FAILURE);
		}
	}
	else
	{
		*err |= VECTOR_ERROR_MASK;
		return (FAILURE);
	}
	return (SUCCESS);
}

int			set_vector(char *str, t_vec3 *vec, int *err)
{
	char **split;

	if (ckeck_vec(str))
	{
		split = ft_split(str, ',');
		if (split != NULL)
		{
			*vec = new_vec_from_char(split[0], split[1], split[2]);
			free_split(split);
		}
		else
		{
			*err |= MALLOC_ERROR_MASK;
			return (FAILURE);
		}
	}
	else
	{
		*err |= VECTOR_ERROR_MASK;
		return (FAILURE);
	}
	return (SUCCESS);
}

int			set_color(char *str, t_col *col, int *err)
{
	char	**split;
	int		ret;

	ret = SUCCESS;
	if (ckeck_col(str))
	{
		split = ft_split(str, ',');
		if (split != NULL)
		{
			*col = char_to_col(split[0], split[1], split[2]);
			free_split(split);
			if (!is_in_range_col(col))
				ret = FAILURE;
		}
		else
		{
			*err |= MALLOC_ERROR_MASK;
			return (FAILURE);
		}
	}
	else
		ret = FAILURE;
	if (ret == FAILURE)
		*err |= COL_ERROR_MASK;
	return (ret);
}
