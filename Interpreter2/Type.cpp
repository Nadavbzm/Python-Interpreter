#include "type.h"

bool Type::isTemp()
{
	return this->_isTemp;
}

void Type::setIsTemp(bool x)
{
	this->_isTemp = x;
}
