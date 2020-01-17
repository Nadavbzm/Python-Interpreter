#ifndef VOID_H
#define VOID_H
#include "Type.h"
class Void : public Type
{
public:
	Void();
	~Void();
	bool isPrintable();
	std::string toString();
	Type * copy();
private:

};

#endif // VOID_H