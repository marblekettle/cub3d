#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

int		main(void)
{
	void *mlx;

	mlx = NULL;
	mlx = mlx_init();
	if (mlx)
		printf("MiniLibX works properly!");
	return (0);
}
