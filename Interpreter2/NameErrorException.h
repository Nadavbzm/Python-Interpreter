#ifndef NAME_ERROR_EXCEPTION_H
#define NAME_ERROR_EXCEPTION_H
#include "InterperterException.h"
class NameErrorException : public InterperterException
{
public:
	NameErrorException(std::string name);
	~NameErrorException();
	std::string what();

private:
	std::string _name;
};

#endif // NAME_ERROR_EXCEPTION_H