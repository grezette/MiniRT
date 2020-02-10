#include "libft.h"
#include <stdio.h>

float	ft_float_atoi(char *str)
{
	int i;
	float	atoi;
	int	minus;
	int aftr;

	aftr = -1;
	atoi = 0;
	minus = 1;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		atoi = atoi * 10 + str[i++] - '0';
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
		atoi = atoi + (str[i++] - '0') * ft_power(10, --aftr);
	atoi *= minus;
	return (atoi);
}

int	main()
{
	printf("%f", ft_float_atoi("62.311111111111"));
	return (0);
}
