#include "List.h"
#include "Parser.h"

List::List(std::vector<std::string> &s)
{ 
	for (int i = 0; i < s.size(); i++)
	{
		this->_value.push_back(Parser::getType(s[i]));
	}
}

bool List::isPrintable()
{
	return true;
}

std::string List::toString()
{
	std::string val = "[";
	for (int i = 0; i < this->_value.size()-1; i++)
	{
		val += this->_value[i]->toString() + ", ";
	}
	val += this->_value[_value.size()-1]->toString() + "]";
	return val;
}

Type * List::copy()
{
	std::vector<std::string> v;
	Type * temp = new List(v);
	/*Type * tempVal;
	std::vector<Type *> vector;
	for (int i = 0; i < this->_value.size(); i++)
	{
		tempVal = this->_value[i]->copy();
		tempVal->setIsTemp(false);
		vector.insert(this->_value.begin(), tempVal);
	}
	temp = new List(vector);
	*/
	return temp;
}

void List::add(Type * x)
{
	this->_value.insert(this->_value.begin(), x);
}

void List::clean()
{
	for (int i = 0; i < this->_value.size(); i++)
	{
		delete(this->_value[i]);
	}
}
