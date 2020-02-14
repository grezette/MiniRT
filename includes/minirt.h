#ifndef MINIRT_H
#define MINIRT_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "SDL/SDL.h"
#include "../Libft/libft.h"
#include "./minirt_struct.h"

void	ft_pars_minirt(t_minirt *minirt, char *file);


/*utils*/
void	ft_exit_error(char *msg, void *elem);

/*parsing utils*/
int		ft_pars_coord(t_coord *coord, char **str);
int		ft_pars_color(t_color *color, char **str);

#endif
