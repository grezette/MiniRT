#include "libft.h"

float	ft_power(float nb, int power)
{
	float ret;

	ret = nb;
	if (!(power))
		return (1);
	else if (power > 0)
		while (power--)
			ret *= nb;
	else
		while (power++)
			ret /= nb;
	return (ret);
}
