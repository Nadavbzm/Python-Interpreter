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


std::string String::operator+=(String * x)
{
	return this->_value + Helper::RemoveStr(x->toString());
}

std::string String::operator*(Integer * x)
{
	std::string t = "\"";
	for (int i = 0; i < x->getValue(); i++)
	{
		t += Helper::RemoveStr(this->toString());
	}
	t += "\"";
	return t;

}