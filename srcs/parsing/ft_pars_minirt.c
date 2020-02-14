#include "../../includes/minirt.h"

static void ft_pars_init(t_minirt *rt)
{
	rt->reso.x = -1;
	rt->reso.y = 0;
	rt->alight.ratio = 2;
	rt->alight.color.red = 0;
	rt->alight.color.green = 0;
	rt->alight.color.blue = 0;
	rt->cam = NULL;
}

void		ft_print_one_cam(t_camera *cam)
{
	printf("x = |%.2f|\ny = |%.2f|\nz = |%.2f|\n", cam->coord.x, cam->coord.y, cam->coord.z);
	printf("vx = |%.2f|\nvy = |%.2f|\nvz = |%.2f|\n", cam->vect.x, cam->vect.y, cam->vect.z);
	printf("fov = |%.2d|\n", cam->fov);
}

t_list		*ft_pars_camera(char **line)
{
	t_camera	cam;
	t_list		*elem;
	char		*tmp;

	tmp = *line;
	tmp++;
	while ((9 <= *tmp && *tmp <= 13) ||*tmp == ' ')
		tmp++;
	if (ft_pars_coord(&(cam.coord), &tmp))
		ft_exit_error("Error file.rt\nCamera: wrong character written in coordinates", *line);
	while ((9 <= *tmp && *tmp <= 13) ||*tmp == ' ')
		tmp++;
	if (ft_pars_coord(&(cam.vect), &tmp))
		ft_exit_error("Error file.rt\nCamera: wrong character written in vectors", *line);
	while ((9 <= *tmp && *tmp <= 13) ||*tmp == ' ')
		tmp++;
	cam.fov = ft_atoi(tmp);
	while (ft_isdigit(*tmp))
		tmp++;
	while ((9 <= *tmp && *tmp <= 13) ||*tmp == ' ')
		tmp++;
	if (cam.vect.x < -1 || cam.vect.x > 1 || cam.vect.y < -1 || cam.vect.y > 1 ||
			cam.vect.z < -1 || cam.vect.z > 1 || *tmp)
		ft_exit_error("Error file.rt\nCamera: wrong character/data in line", *line);
	if (!(elem = ft_lstnew(&cam)))
		ft_exit_error("Error ft_lstnew\nCamera: malloc() didn't worked", *line);
	return (elem);
}

static void	ft_pars_ambiance_light(t_minirt *rt, char **line)
{
	char *tmp;

	tmp = *line;
	tmp++;
	if (rt->alight.ratio != 2)
		ft_exit_error("Error file.rt\nAmbiance light: 2nd time encoutered\n", *line);
	while ((9 <= *tmp && *tmp <= 13) ||*tmp == ' ')
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
		ft_exit_error("Error file.rt\nAmbiance light: Wrong character written in color", *line);
	while ((9 <= *tmp && *tmp <= 13) || *tmp == ' ')
		tmp++;
	if (rt->alight.ratio < 0 || rt->alight.ratio > 1 || *tmp)
		ft_exit_error("Error file.rt\nAmbiance light: Wrong ratio or wrong character", *line);
}

static void ft_pars_resolution(t_minirt *rt, char **line)
{
	int i;

	i = 1;
	if (rt->reso.x != -1)
		ft_exit_error("Error\nResolution is, at least, wriiten 2 times\n", *line);
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
		ft_exit_error("Error\nWrong character written in Resolution line\n", *line);
	if (!rt->reso.x || !rt->reso.y)
		ft_exit_error("Error\nResolution can't be equal to 0\n", *line);
}

static void	ft_pars_affect(t_minirt *rt, char **line)
{
	if (**line == 'R')
		ft_pars_resolution(rt, line);
	else if (**line == 'A')
		ft_pars_ambiance_light(rt, line);
	else if (**line == 'c')
	{
		ft_lstadd_back(&(rt->cam), ft_pars_camera(line));
		ft_print_one_cam((t_camera *)rt->cam->content);
	}
	/*else if (**line == 'l')
	  ft_pars_light(rt, line);
	  else if ((*line)[0] == 'p' && (*line)[1] == 'l')
	  ft_pars_plane(rt, line);
	  else if ((*line)[0] == 's' && (*line)[1] == 'p')
	  ft_pars_sphere(rt, line);
	  else if ((*line)[0] == 's' && (*line)[1] == 'q')
	  ft_pars_square(rt, line);
	  else if ((*line)[0] == 'c' && (*line)[1] == 'y')
	  ft_pars_cylinder(rt, line);
	  else if ((*line)[0] == 't' && (*line)[1] == 'r')
	  ft_pars_triangle(rt, line);
	 */else
	ft_exit_error("Error\nLine not identified\n", *line);
}

void		ft_pars_minirt(t_minirt *rt, char *file)
{
	char 	*line;
	int		fd;
	int		ret;

	ft_pars_init(rt);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit_error("Error\nCouldn't open the file\n", NULL);
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			ft_exit_error("Error\nget_next_line() failed\n", NULL);
		if (*line)
			ft_pars_affect(rt, &line);
		free(line);
	}
	if (*line)
		ft_pars_affect(rt, &line);
	free(line);
	if (close(fd) == -1)
		ft_exit_error("Error\nCouldn't close the file\n", NULL);
}
