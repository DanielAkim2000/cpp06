#include "Serializer.hpp"

#include "Serializer.hpp"

int main()
{
	Data d;

	d.id = 50;
	d.name = "akim";
	std::cout << "Adresse originale : " << &d << std::endl;
	uintptr_t raw = Serializer::serialize(&d);
	std::cout << "Valeur serializee : " << raw << std::endl;
	Data *p = Serializer::deserialize(raw);
	std::cout << "Adresse deserializee : " << p << std::endl;
	if (p == &d)
	{
		std::cout << "Conversion OK" << std::endl;
		std::cout << p->id << std::endl;
		std::cout << p->name << std::endl;
	}
	return (0);
}
