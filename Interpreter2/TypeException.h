#include "InterperterException.h"

class TypeException : public InterperterException
{
public:
	virtual const char* what() const throw();
};
