#include "main.hpp"

Base *generate(void)
{
	int rand = std::rand() % 3;

	if (rand == 0)
		return (new A());
	else if (rand == 1)
		return (new B());
	return (new C());
}

void identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknow type" << std::endl;
}

void identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch (const std::exception &e)
	{
	}

	try
	{
		(void)dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch (const std::exception &e)
	{
	}

	try
	{
		(void)dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch (const std::exception &e)
	{
	}
	std::cout << "Unknown type" << std::endl;
}

int main(void)
{
	std::srand(std::time(NULL));
	Base *b;
	for (int i = 0; i < 5; i++)
	{
		b = generate();
		std::cout << "Identify by *: ";
		identify(b);
		std::cout << "Identify by &: ";
		identify(*b);
		delete b;
	}
}
