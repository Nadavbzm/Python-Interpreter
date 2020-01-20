#include "Integer.h"

Integer::Integer(int x)
{
	this->_value = x;
}

Integer::~Integer()
{
}

bool Integer::isPrintable()
{
	return true;
}

std::string Integer::toString()
{
	return std::to_string(this->_value);
}

Type * Integer::copy()
{
	Type * temp = new Integer(this->_value);
	return temp;
}

int Integer::getValue()
{
	return _value;
}

void Integer::setValue(int x)
{
	_value = x;
}


int Integer::operator+=(Integer * x)
{
	return this->_value + x->getValue();
}

int Integer::operator*(Integer * x)
{
	return this->_value * x->getValue();

}

std::string Integer::operator*(String * x)
{
	std::string t = "\"";
	for (int i = 0; i < this->_value; i++)
	{
		t+= Helper::RemoveStr(x->toString());
	}
	t += "\"";
	return t;

}