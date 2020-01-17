#include "String.h"

String::String(std::string x)
{
	this->_value = x;
}

String::~String()
{
}

inline bool String::isPrintable()
{
	return true;
}

inline std::string String::toString()
{
	return this->_value;
}

Type * String::copy()
{
	Type * temp = new String(this->_value);
	return temp;
}

void String::setValue(std::string x)
{
	_value = x;
}
