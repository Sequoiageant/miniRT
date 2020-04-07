/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 18:32:24 by julien            #+#    #+#             */
/*   Updated: 2020/04/07 16:26:44 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		set_if_in_rnge(char *s, double *d, double min, double max)
{
	*d = ft_atof(s);
	if (*d >= min && *d <= max)
		return (SUCCESS);
	return (FAILURE);
}

int	is_int_or_float(char *str, char sign)
{
	int	i;

	i = 0;
	if (sign == '+')
	{
		if (str[0] == '+')
			i++;
	}
	else if (sign == '-')
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (FALSE);
		if (str[i] == '.' && (str[i + 1] == '.' || str[i + 1] == '\0'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_int(char *str, char sign)
{
	int	i;

	i = 0;
	if (sign == '+')
	{
		if (str[0] == '+')
			i++;
	}
	else if (sign == '-')
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ckeck_vec(char *str)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '.' && str[i] != ','
			&& str[i] != '+' && str[i] != '-')
			return (FALSE);
		if (ft_isdigit(str[i]) && (str[i + 1] == '+' || str[i + 1] == '-'))
			return (FALSE);
		if (str[i] == '.' && (str[i + 1] == '.' || str[i + 1] == '\0'))
			return (FALSE);
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (FALSE);
	return (TRUE);
}

int	is_normal_vec(t_vec3 vec)
{
	return (vec.x >= -1.0 && vec.x <= 1.0
		&& vec.y >= -1.0 && vec.y <= 1.0
		&& vec.z >= -1.0 && vec.z <= 1.0);
}

int	set_normal_vec(char *str, t_vec3 *vec, int *err)
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

int	set_vector(char *str, t_vec3 *vec, int *err)
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

int	ckeck_col(char *str)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (str[0] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != ',')
			return (FALSE);
		if (ft_isdigit(str[i]) && str[i + 1] == '+')
			return (FALSE);
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (FALSE);
	return (TRUE);
}

int	is_in_range_col(t_col *col)
{
	return (col->r >= 0 && col->r <= 255
		&& col->g >= 0 && col->g <= 255
		&& col->b >= 0 && col->b <= 255);
}

int	set_color(char *str, t_col *col, int *err)
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
