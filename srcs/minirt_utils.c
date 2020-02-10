#include <stdlib.h>
#include "../includes/minirt.h"

void	ft_exit_error(char *msg, void *elem)
{
	free(elem);
	elem = NULL;
	write(1, msg, ft_strlen(msg));
	exit(0);
}
