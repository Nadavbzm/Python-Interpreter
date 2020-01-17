#include "TypeException.h"

const char * TypeException::what() const throw()
{
	return "Type Error: Type Mismatch";
}
