/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_parsing_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:34:46 by grezette          #+#    #+#             */
/*   Updated: 2020/02/20 18:06:52 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			ft_pars_init(t_minirt *rt)
{
	rt->reso.x = -1;
	rt->reso.y = 0;
	rt->alight.ratio = 2;
	rt->alight.color.red = 0;
	rt->alight.color.green = 0;
	rt->alight.color.blue = 0;
	rt->cam = NULL;
}

static float	ft_pars_coord_float(char **str)
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
	if (**str == ',')
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
	if (!(ft_isdigit(**str)) && **str != '-')
		return (-1);
	coord->y = ft_pars_coord_float(str);
	if (!(ft_isdigit(**str)) && **str != '-')
		return (-1);
	coord->z = ft_pars_coord_float(str);
	if ((9 <= **str && **str <= 13) || **str == ' ')
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
