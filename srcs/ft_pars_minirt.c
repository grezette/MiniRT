#include "../includes/minirt.h"

static void	ft_pars_ambiance_light(t_minirt *minirt, char **line)
{
	int i;

	i = 0;
	if (minirt->alight.ratio != 2)
		ft_exit_error("Error\nAmbiance light is, at least, wriiten a 2 times\n", *line);
	while ((9 <= (*line)[i] && (*line)[i] <= 13) || (*line)[i] == ' ')
		i++;
	minirt->alight.ratio = ft_atof(&(*line)[i]);
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] == '.')
		i++
	while (ft_isdigit((*line)[i]))
		i++;
	while ((9 <= (*line)[i] && (*line)[i] <= 13) || (*line)[i] == ' ')
		i++;
	while (ft_isdigit((*line)[i]))
		minirt->alight.color.red = minirt->alight.color.red * 10 + (*line)[i++] - '0';
	if ((*line)[i] == ',')
		i++;
	while (ft_isdigit((*line)[i]))
		minirt->alight.color.green = minirt->alight.color.green * 10 + (*line)[i++] - '0';
	if ((*line)[i] == ',')
		i++;
	while (ft_isdigit((*line)[i]))
		minirt->alight.color.blue = minirt->alight.color.blue * 10 + (*line)[i++] - '0';
	while ((9 <= (*line)[i] && (*line)[i] <= 13) || (*line)[i] == ' ')
		i++;
	if (minirt->alight.ratio < 0 || minirt->alight.ratio > 1 || (*line)[i])
		ft_exit_error("Error\n Wrong character written in abiance light line", *line);
}

static void ft_pars_resolution(t_minirt *minirt, char **line)
{
	int i;

	i = 1;
	if (minirt->reso.x != -1)
		ft_exit_error("Error\nResolution is, at least, wriiten 2 times\n", *line);
	while ((9 <= (*line)[i] && (*line)[i] <= 13) || (*line)[i] == ' ')
		i++;
	while (ft_isdigit((*line)[i]))
		minirt->reso.x = minirt->reso.x * 10 + (*line)[i++] - '0';
	while ((9 <= (*line)[i] && (*line)[i] <= 13) || (*line)[i] == ' ')
		i++;
	while (ft_isdigit((*line)[i]))
		minirt->reso.y = minirt->reso.y * 10 + (*line)[i++] - '0';
	while ((9 <= (*line)[i] && (*line)[i] <= 13) || (*line)[i] == ' ')
		i++;
	if ((*line)[i])
		ft_exit_error("Error\nWrong character written in Resolution line\n", *line);
	if (!minirt->reso.x || !minirt->reso.y)
		ft_exit_error("Error\nResolution can't be equal to 0\n", *line);
}

static void	ft_pars_affect(t_minirt *minirt, char **line)
{
	if (**line == 'R')
		ft_pars_resolution(minirt, line);
	else if (**line == 'A')
		ft_pars_ambiance_light(minirt, line);
	/*else if (**line == 'c')
		ft_pars_camera(minirt, line);
	else if (**line == 'l')
		ft_pars_light(minirt, line);
	else if ((*line)[0] == 'p' && (*line)[1] == 'l')
		ft_pars_plane(minirt, line);
	else if ((*line)[0] == 's' && (*line)[1] == 'p')
		ft_pars_sphere(minirt, line);
	else if ((*line)[0] == 's' && (*line)[1] == 'q')
		ft_pars_square(minirt, line);
	else if ((*line)[0] == 'c' && (*line)[1] == 'y')
		ft_pars_cylinder(minirt, line);
	else if ((*line)[0] == 't' && (*line)[1] == 'r')
		ft_pars_triangle(minirt, line);
	*/else
		ft_exit_error("Error\nLine not identified\n", *line);
}

void		ft_pars_minirt(t_minirt *minirt, char *file)
{
	char 	*line;
	int		fd;
	int		ret;

	minirt->reso.x = -1;
	minirt->alight.ratio = 2;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit_error("Error\nCouldn't open the file\n", NULL);
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			ft_exit_error("Error\nget_next_line() failed\n", NULL);
		if (*line)
			ft_pars_affect(minirt, &line);
		free(line);
	}
	if (*line)
		ft_pars_affect(minirt, &line);
	free(line);
	if (close(fd) == -1)
		ft_exit_error("Error\nCouldn't close the file\n", NULL);
}
