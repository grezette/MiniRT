/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:35:02 by grezette          #+#    #+#             */
/*   Updated: 2020/02/22 17:00:22 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_del_one_cam(void *content)
{
	free(content);
	content = 0;
}

void	ft_del_one_obj(void *content)
{
	free(((t_object *)content)->spe);
	((t_object *)content)->spe = 0;
	free(content);
	content = 0;
}

void	ft_exit_error(char *msg, void *elem, t_minirt *rt)
{
	free(elem);
	elem = NULL;
	ft_lstclear(&(rt->cam), *ft_del_one_cam);
	ft_lstclear(&(rt->obj), *ft_del_one_obj);
	write(1, "Error\n", 6);
	write(1, msg, ft_strlen(msg));
	//system("leaks miniRT");
	exit(0);
}
