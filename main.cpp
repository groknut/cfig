

#include <iostream>
#include <fstream>
#include <string>

#include "ic.h"


void helper(const std::string& program);

int main(int argc, char** argv)
{

	if (argc != 2)
	{
		helper(argv[0]);
		return 0;
	}
						
	Ic ic(argv[1]);

	std::cout << ic.as_int("a") << std::endl;
	std::cout << ic.as_int("graph", "b") << std::endl;
	std::cout << ic.as_bool("c") << std::endl;
	std::cout << ic.as_bool("d") << std::endl;
	// std::cout << tol.as_bool("e") << std::endl;

	std::cout << ic.as_double("graph", "k") << std::endl;

	return 0;

}

void helper(const std::string& program)
{
	std::cout << "Example:" << std::endl;
	std::cout << program << "<file>: standard file reading (.ic format)" << std::endl;
}
