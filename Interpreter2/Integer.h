#ifndef INTEGER_H
#define INTEGER_H

#include "Type.h"
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
private:
	int _value;
};

#endif // INTEGER_H