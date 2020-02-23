/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:34:56 by grezette          #+#    #+#             */
/*   Updated: 2020/02/23 13:59:10 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		main(int ac, char **av)
{
	t_minirt	rt;

	if (ac > 3)
		ft_exit_error("Too many argument specified", NULL, &rt);
	ft_pars_minirt(&rt, av[1]);
	return (0);
}
