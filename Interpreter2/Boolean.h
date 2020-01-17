#ifndef BOOLEAN_H
#define BOOLEAN_H
#include "Type.h"

class Boolean : public Type
{
public:
	Boolean(bool x);
	~Boolean();

	bool isPrintable();
	std::string toString();
	Type * copy();
	bool getValue();
	void setValue(bool x);
private:
	bool _value;
};

#endif // BOOLEAN_H