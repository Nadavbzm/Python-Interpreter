#ifndef TYPE_H
#define TYPE_H
#include <string>
class Type
{
public:
	bool isTemp();
	void setIsTemp(bool x);
	virtual bool isPrintable() = 0;
	virtual std::string toString() = 0;
	virtual Type * copy() = 0;

protected:
	bool _isTemp;

};





#endif //TYPE_H
