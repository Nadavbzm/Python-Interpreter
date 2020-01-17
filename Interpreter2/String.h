#ifndef STRING_H
#define STRING_H
#include "Sequence.h"

class String : public Sequence
{
public:
	String(std::string x);
	~String();
	bool isPrintable();
	std::string toString();
	Type * copy();
	void setValue(std::string x);
private:
	std::string _value;
};

#endif // STRING_H