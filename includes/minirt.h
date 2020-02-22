/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 15:55:34 by grezette          #+#    #+#             */
/*   Updated: 2020/02/22 17:24:16 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

//#include "SDL/SDL.h"
# include "../Libft/libft.h"
# include "./minirt_struct.h"

/*main fonctions*/
void	ft_pars_minirt(t_minirt *minirt, char *file);

/*utils*/
void	ft_exit_error(char *msg, void *elem, t_minirt *rt);

/*parsing objects*/
t_list	*ft_pars_obj(t_minirt *rt, int type, char **line, int (*f)(char **, t_union *));
int		ft_pars_light(char **str, t_union *spe);
int		ft_pars_sphere(char **str, t_union *spe);
int		ft_pars_plane(char **str, t_union *spe);
int		ft_pars_square(char **str, t_union *spe);
int		ft_pars_cylinder(char **str, t_union *spe);
int		ft_pars_triangle(char **str, t_union *spe);

/*parsing utils*/
float	ft_pars_coord_float(char **str);
int		ft_pars_coord(t_coord *coord, char **str);
int		ft_pars_color(t_color *color, char **str);
void	ft_pars_init(t_minirt *rt);

/*print parsing */
void	ft_print_reso(t_resolution reso);
void	ft_print_color(t_color color);
void	ft_print_amblight(t_amblight alight);
void	ft_print_coord(t_coord coord);
void	ft_print_one_cam(t_camera *cam);
void	ft_print_all_cam(t_list *camera);
void	ft_print_file(t_minirt *rt);

#endif
