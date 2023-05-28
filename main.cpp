#include <easyx.h>
#include <iostream>
#include "cube.h"
int main(void)
{
	srand(time(0));
	initgraph(1000, 1000);
	Snake snake(20, 20);
	Food food;
	Env start;
	start.Run(snake,food);

	return 0;
}