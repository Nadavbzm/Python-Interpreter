#include "NameErrorException.h"

NameErrorException::NameErrorException(std::string name)
{
	this->_name = name;
}

NameErrorException::~NameErrorException()
{
}

std::string NameErrorException::what()
{
	std::string temp = "NameError : " + _name + "is not defined";
	return temp.c_str();
}
