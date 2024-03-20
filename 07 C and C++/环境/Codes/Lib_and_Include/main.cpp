#include <iostream>
#include "mylib.h"

int main ()
{
	int a = 5, b = 8;
	std::cout << a << '\t' << b << std::endl;
	Swap (a, b);
	std::cout << a << '\t' << b << std::endl;

	return 0;
}
