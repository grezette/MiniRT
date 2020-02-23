/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_parsing_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:34:46 by grezette          #+#    #+#             */
/*   Updated: 2020/02/23 13:54:11 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			ft_pars_init(t_minirt *rt)
{
	rt->reso.x = -1;
	rt->reso.y = 0;
	rt->alight.ratio = 2;
	rt->cam = NULL;
	rt->obj = NULL;
}

float			ft_pars_coord_float(char **str)
{
	float nb;

	nb = ft_atof(*str);
	if (**str == '-')
		(*str)++;
	while (ft_isdigit(**str))
		(*str)++;
	if (**str == '.')
		(*str)++;
	while (ft_isdigit(**str))
		(*str)++;
	return (nb);
}

int				ft_pars_coord(t_coord *coord, char **str)
{
	if ((9 <= **str && **str <= 13) || **str == ' ')
		while ((9 <= **str && **str <= 13) || **str == ' ')
			(*str)++;
	if (!(ft_isdigit(**str)) && **str != '-')
		return (-1);
	coord->x = ft_pars_coord_float(str);
	if (**str == ',')
		(*str)++;
	if (!(ft_isdigit(**str)) && **str != '-')
		return (-1);
	coord->y = ft_pars_coord_float(str);
	if (**str == ',')
		(*str)++;
	if (!(ft_isdigit(**str)) && **str != '-')
		return (-1);
	coord->z = ft_pars_coord_float(str);
	while ((9 <= **str && **str <= 13) || **str == ' ')
		(*str)++;
	if (ft_isdigit(**str) || **str == '-')
		return (0);
	return (-1);
}

int				ft_pars_color(t_color *color, char **str)
{
	if (!(ft_isdigit(**str)))
		return (-1);
	color->red = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	if (!(ft_isdigit(**str)))
		return (-1);
	color->green = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	if (!(ft_isdigit(**str)))
		return (-1);
	color->blue = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	while ((9 <= **str && **str <= 13) || **str == ' ')
		(*str)++;
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
