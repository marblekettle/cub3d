#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	char line[10];
	unsigned int val;

	ft_bzero(line, 10);
	read(0, line, 10);
	val = (unsigned int)ft_atoi(line);
	if (val > (unsigned char)val)
		printf("Out of bounds\n");
	else
		printf("In bounds\n");
	return (0);
}