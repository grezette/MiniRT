/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_pars_objects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:10:50 by grezette          #+#    #+#             */
/*   Updated: 2020/02/23 13:54:25 by grezette         ###   ########.fr       */
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

int		ft_pars_cylinder(char **str, t_union *spe)
{
	if (ft_pars_coord(&(spe->cylinder.vect), str))
		return (-1);
	spe->cylinder.diam = ft_pars_coord_float(str);
	while ((9 <= **str && **str <= 13) || **str == ' ')
		(*str)++;
	spe->cylinder.height = ft_pars_coord_float(str);
	while ((9 <= **str && **str <= 13) || **str == ' ')
		(*str)++;
	if (spe->cylinder.vect.x < 0 || spe->cylinder.vect.x > 1 ||
			spe->cylinder.vect.y < 0 || spe->cylinder.vect.y > 1 ||
			spe->cylinder.vect.z < 0 || spe->cylinder.vect.z > 1 ||
			spe->cylinder.diam < 0 || spe->cylinder.height < 0 ||
			!(ft_isdigit(**str)))
		return (-1);
	return (0);
}

int		ft_pars_triangle(char **str, t_union *spe)
{
	if (ft_pars_coord(&(spe->triangle.sndpoint), str))
		return (-1);
	if (ft_pars_coord(&(spe->triangle.trdpoint), str))
		return (-1);
	if (!(ft_isdigit(**str)))
		return (-1);
	return (0);
}
