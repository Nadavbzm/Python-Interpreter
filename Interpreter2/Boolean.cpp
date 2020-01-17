#include "Boolean.h"

Boolean::Boolean(bool x)
{
	this->_value = x;
}

Boolean::~Boolean()
{
}


bool Boolean::isPrintable()
{
	return true;
}

std::string Boolean::toString()
{
	return std::to_string(this->_value);
}

Type * Boolean::copy()
{
	Type * temp = new Boolean(this->_value);
	return temp;
}

bool Boolean::getValue()
{
	return _value;
}

void Boolean::setValue(bool x)
{
	_value = x;
}
