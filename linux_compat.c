#include "linux_compat.h"
#include <stdlib.h>
#include <stdint.h>

void	mlx_sync(int a, void *b)
{
	a = 0;
	b = NULL;
}