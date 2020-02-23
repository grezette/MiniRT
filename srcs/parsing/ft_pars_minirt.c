/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_minirt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:34:28 by grezette          #+#    #+#             */
/*   Updated: 2020/02/23 13:47:02 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_list	*ft_pars_camera(t_minirt *rt, char **line)
{
	t_camera	*cam;
	t_list		*elem;
	char		*tmp;

	if (!(cam = (t_camera *)malloc(sizeof(t_camera))))
		ft_exit_error("Camera: Failed mallocing cam", *line, rt);
	tmp = *line;
	tmp++;
	if (ft_pars_coord(&(cam->coord), &tmp))
		ft_exit_error("Camera: wrong character written in coord", *line, rt);
	if (ft_pars_coord(&(cam->vect), &tmp))
		ft_exit_error("Camera: wrong character written in vectors", *line, rt);
	cam->fov = ft_atoi(tmp);
	while (ft_isdigit(*tmp))
		tmp++;
	while ((9 <= *tmp && *tmp <= 13) || *tmp == ' ')
		tmp++;
	if (cam->vect.x < -1 || cam->vect.x > 1 || cam->vect.y < -1 || cam->fov > 180 ||
			cam->vect.y > 1 || cam->vect.z < -1 || cam->vect.z > 1 || *tmp)
		ft_exit_error("Camera: wrong character/data in line", *line, rt);
	if (!(elem = ft_lstnew(cam)))
		ft_exit_error("Camera: ft_lstnew() didn't worked", *line, rt);
	return (elem);
}

static void	ft_pars_ambiance_light(t_minirt *rt, char **line)
{
	char *tmp;

	tmp = *line;
	tmp++;
	if (rt->alight.ratio != 2)
		ft_exit_error("Ambiance light: 2nd time encoutered\n", *line, rt);
	while ((9 <= *tmp && *tmp <= 13) || *tmp == ' ')
		tmp++;
	rt->alight.ratio = ft_atof(tmp);
	while (ft_isdigit(*tmp))
		tmp++;
	if (*tmp == '.')
		tmp++;
	while (ft_isdigit(*tmp))
		tmp++;
	while ((9 <= *tmp && *tmp <= 13) || *tmp == ' ')
		tmp++;
	if (ft_pars_color(&(rt->alight.color), &tmp))
		ft_exit_error("Amb light: Wrong character written in color", *line, rt);
	if (rt->alight.ratio < 0 || rt->alight.ratio > 1 || *tmp)
		ft_exit_error("Amb light: Wrong ratio or wrong character", *line, rt);
}

static void	ft_pars_resolution(t_minirt *rt, char **line)
{
	int i;

	i = 1;
	if (rt->reso.x != -1)
		ft_exit_error("Resolution is, at least, wriiten 2 times\n", *line, rt);
	rt->reso.x = 0;
	while ((9 <= (*line)[i] && (*line)[i] <= 13) || (*line)[i] == ' ')
		i++;
	while (ft_isdigit((*line)[i]))
		rt->reso.x = rt->reso.x * 10 + (*line)[i++] - '0';
	while ((9 <= (*line)[i] && (*line)[i] <= 13) || (*line)[i] == ' ')
		i++;
	while (ft_isdigit((*line)[i]))
		rt->reso.y = rt->reso.y * 10 + (*line)[i++] - '0';
	while ((9 <= (*line)[i] && (*line)[i] <= 13) || (*line)[i] == ' ')
		i++;
	if ((*line)[i])
		ft_exit_error("Wrong character written in Reso line\n", *line, rt);
	if (!rt->reso.x || !rt->reso.y)
		ft_exit_error("Resolution can't be equal to 0\n", *line, rt);
}

static void	ft_pars_affect(t_minirt *rt, char **line)
{
	if (**line == 'R')
		ft_pars_resolution(rt, line);
	else if (**line == 'A')
		ft_pars_ambiance_light(rt, line);
	else if ((*line)[0] == 'c' && (*line)[1] != 'y')
		ft_lstadd_back(&(rt->cam), ft_pars_camera(rt, line));
	else if (**line == 'l')
		ft_lstadd_back(&(rt->obj), ft_pars_obj(rt, LIGHT, line, *ft_pars_light));
	else if ((*line)[0] == 'p' && (*line)[1] == 'l')
		ft_lstadd_back(&(rt->obj), ft_pars_obj(rt, PLANE, line, *ft_pars_plane));
	else if ((*line)[0] == 's' && (*line)[1] == 'p')
		ft_lstadd_back(&(rt->obj), ft_pars_obj(rt, SPHERE, line, *ft_pars_sphere));
	else if ((*line)[0] == 's' && (*line)[1] == 'q')
		ft_lstadd_back(&(rt->obj), ft_pars_obj(rt, SQUARE, line, *ft_pars_square));
	else if ((*line)[0] == 'c' && (*line)[1] == 'y')
		ft_lstadd_back(&(rt->obj), ft_pars_obj(rt, CYLINDER, line, *ft_pars_cylinder));
	else if ((*line)[0] == 't' && (*line)[1] == 'r')
		ft_lstadd_back(&(rt->obj), ft_pars_obj(rt, TRIANGLE, line, *ft_pars_triangle));
	else
		ft_exit_error("Line not identified\n", *line, rt);
}

void		ft_pars_minirt(t_minirt *rt, char *file)
{
	char	*line;
	int		fd;
	int		ret;

	ft_pars_init(rt);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit_error("Couldn't open the file\n", NULL, rt);
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			ft_exit_error("get_next_line() failed\n", NULL, rt);
		if (*line)
			ft_pars_affect(rt, &line);
		free(line);
	}
	if (*line)
		ft_pars_affect(rt, &line);
	//Le free peut peut-etre abort dans le cadre d'un fichier texte ne finissant pas sur un '\n'
	free(line);
	if (close(fd) == -1)
		ft_exit_error("Couldn't close the file\n", NULL, rt);
	if (rt->reso.x == -1 || rt->alight.ratio == 2)
		ft_exit_error("File .rt: not enough data", NULL, rt);
}
