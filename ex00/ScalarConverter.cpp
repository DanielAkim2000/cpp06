#include "ScalarConverter.hpp"
#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <sstream>

static bool isPseudoLiteral(const std::string &val, bool &isDouble, bool &isFloat)
{
	static const std::string pseudoDoubles[] = {"nan", "+inf", "-inf", "inf"};
	static const std::string pseudoFloats[] = {"nanf", "+inff", "-inff", "inff"};

	isDouble = false;
	isFloat = false;
	for (size_t i = 0; i < 4; ++i)
	{
		if (val == pseudoDoubles[i])
			isDouble = true;
		if (val == pseudoFloats[i])
			isFloat = true;
	}
	return (isDouble || isFloat);
}

static bool isCharLiteral(const std::string &val, char &charValue)
{
	if (val.size() == 3 && val[0] == '\'' && val[2] == '\'')
	{
		charValue = val[1];
		return (true);
	}
	if (val.size() == 1 && !std::isdigit(static_cast<unsigned char>(val[0])))
	{
		charValue = val[0];
		return (true);
	}
	return (false);
}

static bool isIntLiteral(const std::string &val)
{
	if (val.empty())
		return (false);
	size_t i = 0;
	if (val[i] == '+' || val[i] == '-')
		++i;
	if (i >= val.size())
		return (false);
	for (; i < val.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(val[i])))
			return (false);
	}
	return (true);
}

static bool hasDotOrExp(const std::string &val)
{
	for (size_t i = 0; i < val.size(); ++i)
	{
		if (val[i] == '.' || val[i] == 'e' || val[i] == 'E')
			return (true);
	}
	return (false);
}

static bool isFloatLiteral(const std::string &val)
{
	if (val.size() <= 1 || val[val.size() - 1] != 'f')
		return (false);
	std::string core = val.substr(0, val.size() - 1);
	if (!hasDotOrExp(core))
		return (false);
	char *end = NULL;
	errno = 0;
	std::strtod(core.c_str(), &end);
	return (end && *end == '\0' && errno != ERANGE);
}

static bool isDoubleLiteral(const std::string &val)
{
	if (!hasDotOrExp(val))
		return (false);
	char *end = NULL;
	errno = 0;
	std::strtod(val.c_str(), &end);
	return (end && *end == '\0' && errno != ERANGE);
}

static double toDouble(const std::string &val, bool isChar, char charValue, bool isInt, bool isFloat)
{
	if (isChar)
		return (static_cast<double>(charValue));
	if (isInt)
		return (static_cast<double>(std::strtol(val.c_str(), NULL, 10)));
	if (isFloat)
		return (std::strtod(val.substr(0, val.size() - 1).c_str(), NULL));
	return (std::strtod(val.c_str(), NULL));
}

static void printAllImpossible()
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}

static void printPseudoLiteral(const std::string &val, bool isPseudoDouble)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if (isPseudoDouble)
		std::cout << "float: " << val << "f" << std::endl;
	else
		std::cout << "float: " << val << std::endl;
	if (isPseudoDouble)
		std::cout << "double: " << val << std::endl;
	else
		std::cout << "double: " << val.substr(0, val.size() - 1) << std::endl;
}

static void detectKinds(const std::string &val, bool &isChar, char &charValue, bool &isInt, bool &isFloat, bool &isDouble)
{
	isChar = isCharLiteral(val, charValue);
	isInt = (!isChar && isIntLiteral(val));
	isFloat = (!isChar && !isInt && isFloatLiteral(val));
	isDouble = (!isChar && !isInt && !isFloat && isDoubleLiteral(val));
}

static void printChar(double d)
{
	std::cout << "char: ";
	if (std::isnan(d) || std::isinf(d) || d < std::numeric_limits<char>::min() || d > std::numeric_limits<char>::max())
	{
		std::cout << "impossible" << std::endl;
		return;
	}
	char c = static_cast<char>(d);
	if (std::isprint(static_cast<unsigned char>(c)))
		std::cout << c << std::endl;
	else
		std::cout << "Non displayable" << std::endl;
}

static void printInt(double d)
{
	std::cout << "int: ";
	if (std::isnan(d) || std::isinf(d) || d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
	{
		std::cout << "impossible" << std::endl;
		return;
	}
	std::cout << static_cast<int>(d) << std::endl;
}

static void printFloat(double d)
{
	std::cout << "float: ";
	if (std::isnan(d))
	{
		std::cout << "nanf" << std::endl;
		return;
	}
	if (std::isinf(d))
	{
		std::cout << (std::signbit(d) ? "-inff" : "+inff") << std::endl;
		return;
	}
	if (std::fabs(d) > std::numeric_limits<float>::max())
	{
		std::cout << "impossible" << std::endl;
		return;
	}
	float f = static_cast<float>(d);
	double intPart = 0.0;
	std::ostringstream out;
	if (std::modf(static_cast<double>(f), &intPart) == 0.0)
		out << std::fixed << std::setprecision(1) << f;
	else
		out << std::setprecision(std::numeric_limits<float>::digits10) << f;
	std::cout << out.str() << "f" << std::endl;
}

static void printDouble(double d)
{
	std::cout << "double: ";
	if (std::isnan(d))
	{
		std::cout << "nan" << std::endl;
		return;
	}
	if (std::isinf(d))
	{
		std::cout << (std::signbit(d) ? "-inf" : "+inf") << std::endl;
		return;
	}
	double intPart = 0.0;
	std::ostringstream out;
	if (std::modf(d, &intPart) == 0.0)
		out << std::fixed << std::setprecision(1) << d;
	else
		out << std::setprecision(std::numeric_limits<double>::digits10) << d;
	std::cout << out.str() << std::endl;
}

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
	bool isPseudoDouble = false;
	bool isPseudoFloat = false;
	if (isPseudoLiteral(val, isPseudoDouble, isPseudoFloat))
	{
		printPseudoLiteral(val, isPseudoDouble);
		return;
	}

	char charValue = '\0';
	bool isChar = false;
	bool isInt = false;
	bool isFloat = false;
	bool isDouble = false;
	detectKinds(val, isChar, charValue, isInt, isFloat, isDouble);

	if (!isChar && !isInt && !isFloat && !isDouble)
	{
		printAllImpossible();
		return;
	}

	double d = toDouble(val, isChar, charValue, isInt, isFloat);

	printChar(d);
	printInt(d);
	printFloat(d);
	printDouble(d);
}
