#ifndef PARSER_H
#define PARSER_H

#include "InterperterException.h"
#include "IndentationException.h"
#include "SyntaxException.h"
#include "TypeException.h"
#include "type.h"
#include "Helper.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>

#define MAX_MUL_STR 100000

class Parser
{
public:
	static Type* parseString(std::string str) throw();
	static Type* getType(std::string &str);
	static void clean();

private:
	static std::unordered_map<std::string, Type *> _variables;
	static bool isLegalVarName(const std::string& str);
	static bool makeAssignment(const std::string& str);
	static Type* getVariableValue(const std::string &str);

};

#endif //PARSER_H
