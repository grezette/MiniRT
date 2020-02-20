/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_pars_objects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:10:50 by grezette          #+#    #+#             */
/*   Updated: 2020/02/20 18:06:49 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_list	*ft_pars_obj(t_minirt *rt, int type, char **line, void (*f)(char **, t_union *))
{
	t_object	*obj;
	t_list		*elem;
	char		*tmp;

	if (!(obj = (t_object *)malloc(sizeof(t_object))))
		ft_exit_error("Failled mallocing obj", *line, rt);
	obj->type = type;
	tmp = *line;
	while (ft_isalpha(*tmp))
		tmp++;
	if (ft_pars_coord(&(obj->coord), &tmp))
		ft_exit_error("Object: wrong caracter written in coord", *line, rt);
	(*f)(&tmp, obj->spe);
	if (ft_pars_color(&(obj->color), &tmp))
		ft_exit_error("Object: Wrong character written in color", *line, rt);
	if (!(elem = ft_lstnew(obj)))
		ft_exit_error("Object: ft_lstnew() didn't worked", *line, rt);
	return (elem);
}
