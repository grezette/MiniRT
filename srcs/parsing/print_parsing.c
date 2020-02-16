/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:33:48 by grezette          #+#    #+#             */
/*   Updated: 2020/02/16 15:34:02 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void		ft_print_reso(t_resolution reso)
{
	printf("R ");
	printf("|%d| |%d|\n", reso.x, reso.y);
}

void		ft_print_color(t_color color)
{
	printf(" |%d|", color.red);
	printf(",|%d|", color.green);
	printf(",|%d|", color.blue);
}

void		ft_print_amblight(t_amblight alight)
{
	printf("A ");
	printf("|%f|", alight.ratio);
	ft_print_color(alight.color);
}

void		ft_print_coord(t_coord coord)
{
	printf(" |%f|", coord.x);
	printf(",|%f|", coord.y);
	printf(",|%f|", coord.z);
}

void		ft_print_one_cam(t_camera *cam)
{
	printf("c");
	ft_print_coord(cam->coord);
	printf(" |%.2d|\n", cam->fov);
}

void		ft_print_all_cam(t_list *camera)
{
	while (camera)
	{
		ft_print_one_cam((t_camera *)camera->content);
		camera = camera->next;
	}
}

void		ft_print_file(t_minirt *rt)
{
	ft_print_reso(rt->reso);
	ft_print_amblight(rt->alight);
	ft_print_all_cam(rt->cam);
}
