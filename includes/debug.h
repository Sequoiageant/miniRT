/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 18:52:42 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/10 18:58:20 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

void	print_split(char **tab);
int		ft_lstsize(t_obj *lst);
void	print_obj(t_obj *objlst);
void	print_lights(t_light *lights);
void	print_cams(t_cam *cams);

#endif