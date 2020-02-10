#include "../includes/minirt.h"

int		main(int ac, char **av)
{
	t_minirt	minirt;
	(void)ac;
	ft_pars_minirt(&minirt, av[1]);
	return (0);
}
