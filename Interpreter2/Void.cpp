#include "Void.h"
Void::Void()
{
}

Void::~Void()
{
}
inline bool Void::isPrintable()
{
	return false;
}

std::string Void::toString()
{
	return "";
}

Type * Void::copy()
{
	Type * temp = new Void();
	return temp;
}
