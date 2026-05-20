#include "ScalarConverter.hpp"
#include <sstream>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	*this = other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	if (this != &other)
	{
	}
	return (*this);
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(std::string const val)
{
	if (val == "nan")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
		return;
	}
	std::istringstream ss(val);
	double d;
	ss >> d;

	char c = static_cast<char>(d);
	int i = static_cast<int>(d);
	float f = static_cast<float>(d);

	if (std::isprint(c))
		std::cout << "char:   " << c << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	std::cout << "int:    " << i << std::endl;
	std::cout << "float:  " << f << "f" << std::endl;
	std::cout << "double: " << d << std::endl;
}
