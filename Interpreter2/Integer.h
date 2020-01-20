#ifndef INTEGER_H
#define INTEGER_H

#include "Type.h"
#include "Helper.h"
#include "String.h"

class String;
class Integer : public Type
{
public:
	Integer(int x);
	~Integer();
	bool isPrintable();
	std::string toString();
	Type * copy();
	int getValue();
	void setValue(int x);
	int operator+=(Integer * x);
	int operator*(Integer * x);
	std::string operator*(String * x);
private:
	int _value;
};

#endif // INTEGER_H