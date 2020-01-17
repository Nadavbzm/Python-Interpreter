#ifndef LIST_H
#define LIST_H
#include <vector>
#include "Sequence.h"
class List : public Sequence
{
public:
	List(std::vector<std::string> &s);
	bool isPrintable();
	std::string toString();
	Type * copy();
	void add(Type * x);
	void clean();
private:
	std::vector<Type *> _value;
};

#endif // LIST_H