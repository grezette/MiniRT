/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:33:48 by grezette          #+#    #+#             */
/*   Updated: 2020/02/23 13:36:18 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void		ft_print_reso(t_resolution reso)
{
	printf("R:\t\t\t\t");
	printf("%d %d\n", reso.x, reso.y);
}

void		ft_print_color(t_color color)
{
	printf("\t%d", color.red);
	printf(",%d", color.green);
	printf(",%d", color.blue);
}

void		ft_print_amblight(t_amblight alight)
{
	printf("A:\t\t\t\t");
	printf("%f\t\t\t\t\t\t\t\t\t\t", alight.ratio);
	ft_print_color(alight.color);
	printf("\n");
}

void		ft_print_coord(t_coord coord)
{
	printf(" %f", coord.x);
	printf(",%f", coord.y);
	printf(",%f\t", coord.z);
}

void		ft_print_one_cam(t_camera *cam)
{
	ft_print_coord(cam->coord);
	printf(" %.2d\n", cam->fov);
}

void		ft_print_all_cam(t_list *camera)
{
	int i;

	i = 0;
	printf("\n");
	while (camera)
	{
		printf("c n*%3d:\t\t", i++);
		ft_print_one_cam((t_camera *)camera->content);
		camera = camera->next;
	}
}

void		ft_print_one_obj(t_object *obj)
{
	if (obj->type == 0)
		printf("LIGHT\t");
	else if (obj->type == 1)
		printf("SPHERE\t");
	else if (obj->type == 2)
		printf("PLANE\t");
	else if (obj->type == 3)
		printf("SQUARE\t");
	else if (obj->type == 4)
		printf("CYLINDER\t");
	else if (obj->type == 5)
		printf("TRIANGLE\t");
	ft_print_coord(obj->coord);
	if (obj->type == 0)
		printf(" %f\t\t\t\t\t\t\t", obj->spe->r);
	else if (obj->type == 1)
		printf(" %f\t\t\t\t\t\t\t", obj->spe->r);
	else if (obj->type == 2)
	{
		ft_print_coord(obj->spe->plane);
		printf("\t\t\t\t");
	}
	else if (obj->type == 3)
	{
		ft_print_coord(obj->spe->square.vect);
		printf(" %f\t\t\t", obj->spe->square.height);
	}
	else if (obj->type == 4)
	{
		ft_print_coord(obj->spe->cylinder.vect);
		printf(" %f\t", obj->spe->cylinder.diam);
		printf(" %f\t", obj->spe->cylinder.height);
	}
	else if (obj->type == 5)
	{
		ft_print_coord(obj->spe->triangle.sndpoint);
		ft_print_coord(obj->spe->triangle.trdpoint);
	}
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
