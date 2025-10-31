

#include <iostream>
#include <fstream>
#include "ic.h"

int main()
{

	Ic ic("test");

	std::cout << ic.as_int("a") << std::endl;
	std::cout << ic.as_int("graph", "b") << std::endl;
	std::cout << ic.as_bool("c") << std::endl;
	std::cout << ic.as_bool("d") << std::endl;
	// std::cout << tol.as_bool("e") << std::endl;

	std::cout << ic.as_double("graph", "k") << std::endl;

	

	return 0;

}
