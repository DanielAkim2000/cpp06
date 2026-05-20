#include "Serializer.hpp"

Serializer::Serializer() {}

Serializer::Serializer(const Serializer &other)
{
	*this = other;
}

Serializer &Serializer::operator=(const Serializer &other)
{
	if (this != &other)
	{
	}
	return (*this);
}

uintptr_t Serializer::serialize(Data *ptr)
{
	uintptr_t val = reinterpret_cast<uintptr_t>(ptr);
	return val;
}

Data *Serializer::deserialize(uintptr_t raw)
{
	Data *data = reinterpret_cast<Data *>(raw);
	return data;
}
