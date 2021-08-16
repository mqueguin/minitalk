#include <signal.h>
#include <stdio.h>
#include "libft/libft.h"

int	main(void)
{
	char	buff[1000];
	char *str = "coucou";
	ft_memset(buff, 0, 1000);
	int i = 0;
	int	bitmask = 128;
	int j = -1;
	while (str[i])
	{
		bitmask = 128;
		while (bitmask)
		{
			if (bitmask & str[i])
			{
				printf("Le cas ou le bit est egal a 1\n");
				buff[j] = 1;
			}
			else
			{
				printf("Le cas ou le bit est egal a 0\n");
				buff[j] = 0;
			}
			bitmask = bitmask >> 1;
		}
		i++;
	}
	printf("Valeur de buff : %s\n", buff);
	return (0);
}
