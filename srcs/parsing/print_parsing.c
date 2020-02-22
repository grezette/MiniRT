/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:33:48 by grezette          #+#    #+#             */
/*   Updated: 2020/02/22 18:15:37 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void		ft_print_reso(t_resolution reso)
{
	printf("R: ");
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
	printf("A: ");
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
	ft_print_coord(cam->coord);
	printf(" |%.2d|\n", cam->fov);
}

void		ft_print_all_cam(t_list *camera)
{
	int i;

	i = 0;
	while (camera)
	{
		printf("\nc n*%3d: ", i++);
		ft_print_one_cam((t_camera *)camera->content);
		camera = camera->next;
	}
}

void		ft_print_one_obj(t_object *obj)
{
	if (obj->type == 0)
		printf("LIGHT");
	else if (obj->type == 1)
		printf("SPHERE");
	else if (obj->type == 2)
		printf("PLANE");
	else if (obj->type == 3)
		printf("SQUARE");
	else if (obj->type == 4)
		printf("CYLINDER");
	else if (obj->type == 5)
		printf("TRIANGLE");
	ft_print_coord(obj->coord);
	if (obj->type == 0)
		printf(" |%f|", obj->spe->r);
	else if (obj->type == 1)
		printf(" |%f|", obj->spe->r);
	else if (obj->type == 2)
		ft_print_coord(obj->spe->plane);
	else if (obj->type == 3)
	{
		ft_print_coord(obj->spe->square.vect);
		printf(" |%f|", obj->spe->square.height);
	}
	else if (obj->type == 4)
		printf("CYLINDER");
	else if (obj->type == 5)
		printf("TRIANGLE");
	ft_print_color(obj->color);
}

void		ft_print_all_obj(t_list *obj)
{
	int i;

	i = 0;
	while (obj)
	{
		printf("\nobj n*%3d: ", i++);
		ft_print_one_obj((t_object *)obj->content);
		obj = obj->next;
	}
}

void		ft_print_file(t_minirt *rt)
{
	ft_print_reso(rt->reso);
	ft_print_amblight(rt->alight);
	ft_print_all_cam(rt->cam);
	ft_print_all_obj(rt->obj);
}
