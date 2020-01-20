#ifndef STRING_H
#define STRING_H
#include "Sequence.h"
#include "Helper.h"
#include "Integer.h"


class Integer;
class String : public Sequence
{
public:
	String(std::string x);
	~String();
	bool isPrintable();
	std::string toString();
	Type * copy();
	void setValue(std::string x);
	std::string operator+=(String * x);
	std::string operator*(Integer * x);
private:
	std::string _value;
};

#endif // STRING_H