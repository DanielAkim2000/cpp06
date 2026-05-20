#include "ScalarConverter.hpp"

int main(int ac, char **av)
{
	if (ac <= 1)
	{
		std::cout << std::endl;
		return (0);
	}
	for (int i = 1; i < ac; i++)
	{
		ScalarConverter::convert(av[i]);
	}
	return (0);
}
