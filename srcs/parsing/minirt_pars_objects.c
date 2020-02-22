/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_pars_objects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:10:50 by grezette          #+#    #+#             */
/*   Updated: 2020/02/22 18:18:24 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int		ft_pars_light(char **str, t_union *spe)
{
	spe->r = ft_pars_coord_float(str);
	while ((9 <= **str && **str <= 13) || **str == ' ')
		(*str)++;
	if (spe->r < 0 || spe->r > 1 || !(ft_isdigit(**str)))
		return (-1);
	return (0);
}

int		ft_pars_sphere(char **str, t_union *spe)
{
	spe->r = ft_pars_coord_float(str);
	while ((9 <= **str && **str <= 13) || **str == ' ')
		(*str)++;
	if (!(ft_isdigit(**str)))
		return (-1);
	return (0);
}

int		ft_pars_plane(char **str, t_union *spe)
{
	if (ft_pars_coord(&(spe->plane), str))
		return (-1);
	if (spe->plane.x < 0 || spe->plane.x > 1 || spe->plane.y < 0 ||
			spe->plane.y > 1 || spe->plane.z < 0 || spe->plane.z > 1 ||
			!(ft_isdigit(**str)))
		return (-1);
	return (0);
}

int		ft_pars_square(char **str, t_union *spe)
{
	if (ft_pars_coord(&(spe->square.vect), str))
		return (-1);
	spe->square.height = ft_pars_coord_float(str);
	while ((9 <= **str && **str <= 13) || **str == ' ')
		(*str)++;
	if (spe->square.vect.x < 0 || spe->square.vect.x > 1 ||
			spe->square.vect.y < 0 || spe->square.vect.y > 1 ||
			spe->square.vect.z < 0 || spe->square.vect.z > 1 ||
			spe->square.height < 0 || !(ft_isdigit(**str)))
		return (-1);
	return (0);
}

t_list	*ft_pars_obj(t_minirt *rt, int type, char **line, int (*f)(char **, t_union *))
{
	t_object	*obj;
	t_list		*elem;
	char		*tmp;

	if (!(obj = (t_object *)malloc(sizeof(t_object))))
		ft_exit_error("Object: Failled mallocing obj", *line, rt);
	if (!(obj->spe = (t_union *)malloc(sizeof(t_union))))
		ft_exit_error("Object: Failled mallocing spe", *line, rt);
	obj->type = type;
	tmp = *line;
	while (ft_isalpha(*tmp))
		tmp++;
	if (ft_pars_coord(&(obj->coord), &tmp))
		ft_exit_error("Object: wrong caracter written in coord", *line, rt);
	if ((*f)(&tmp, obj->spe))
		ft_exit_error("Object: bad char between coord and color", *line, rt);
	if (ft_pars_color(&(obj->color), &tmp))
		ft_exit_error("Object: Wrong character written in color", *line, rt);
	if (!(elem = ft_lstnew(obj)))
		ft_exit_error("Object: ft_lstnew() didn't worked", *line, rt);
	return (elem);
}
