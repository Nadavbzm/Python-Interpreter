#include "parser.h"
#include <iostream>
#include <cstring>
#include "Integer.h";
#include "Boolean.h"
#include "String.h"
#include "Void.h"
#include "List.h"

std::unordered_map<std::string, Type *> Parser::_variables;

Type* Parser::parseString(std::string str) throw()
{
	if (str == "clear")
	{
		system("cls");
	}

	else if (str.length() > 0)
	{
		if (str[0] == ' ' || str[0] == '	')
		{
			IndentationException e;
			throw e;
		}
		Type * var = Parser::getVariableValue(str);
		if (var != NULL)
		{
			return var;
		}
		Type *  temp = Parser::getType(str);
		if (temp != NULL)
		{
			return temp;
		}
		bool AsignmentSuccefull = Parser::makeAssignment(str);
		if (AsignmentSuccefull)
		{
			Void * v = new Void();
			v->setIsTemp(true);
			return v;
		}
		std::string tempName = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb = ";
		std::string a = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
		std::string t = tempName + str;
		AsignmentSuccefull = Parser::makeAssignment(t);
		if (AsignmentSuccefull)
		{
			std::cout << Parser::_variables.find(a)->second->toString() << std::endl;
			Parser::_variables.erase(tempName);
		}
		if (temp == NULL && !AsignmentSuccefull)
		{
			SyntaxException e;
			throw e;
		}

		
		//std::cout << str << std::endl;
	}
	Void * TempVoid = new Void();
	TempVoid->setIsTemp(true);
	return TempVoid;
}

Type * Parser::getType(std::string & str)
{
	Helper::trim(str);
	bool flag = true;

	//Integer check
	if(Helper::isInteger(str))
	{
		Integer * temp = new Integer(atoi(str.c_str()));
		temp->setIsTemp(true);
		return temp;
	}
	if (Helper::isBoolean(str))
	{
		Boolean * temp = new Boolean(str == "True");
		temp->setIsTemp(true);
		return temp;
	}
	if (Helper::isString(str))
	{
		String * temp = new String(str);
		temp->setIsTemp(true);
		return temp;
	}
	if (Helper::isList(str))
	{
		std::vector<std::string> v;
		int count = 0;
		int next = 0;
		std::string temp = "";
		for (int i = 1; i < str.length(); i++)
		{
			if (str[i] == ',' || i==str.length()-1)
			{
				i++;
				v.push_back(temp);
				temp = "";
			}
			temp += str[i];
		}
		List * l = new List(v);
		l->setIsTemp(false);
		return l;
	}
	return NULL;

}

bool Parser::isLegalVarName(const std::string & str)
{
	if (!(Helper::isLetter(str[0]) || str[0] == '_'))
	{
		return false;
	}
	for (int i = 1; i < str.length(); i++)
	{
		if (!(Helper::isDigit(str[i]) || Helper::isLetter(str[0]) || str[0] == '_'))
		{
			return false;
		}
	}
	return true;
}

bool Parser::makeAssignment(const std::string & str)
{
	if (str.find('=') == std::string::npos)
	{
		return false;
	}
	else
	{
		int index = str.find('=');
		std::string name = "";
		std::string value = "";
		for (int i = 0; i < index; i++)
		{
			name += str[i];
		}
		if (!Parser::isLegalVarName(name))
		{
			return false;
		}
		Helper::trim(name);
		if (index < str.length())
		{
			for (int i = index + 1; i < str.length(); i++)
			{
				value += str[i];
			}
		}
		Type *  tempType = Parser::getType(value);
		if (tempType != NULL)
		{
			Helper::trim(name);
			std::unordered_map<std::string, Type * >::iterator iter = Parser::_variables.find(name);
			if (iter != Parser::_variables.end())
			{
				iter->second = tempType;
			}
			Helper::trim(name);
			tempType->setIsTemp(false);
			Parser::_variables.insert({ name, tempType });
			return true;
		}
		Helper::trim(value);
		std::unordered_map<std::string, Type *>::iterator i = Parser::_variables.find(value);
		if (i != Parser::_variables.end())
		{
			Helper::trim(name);
			Type * temp = i->second->copy();
			temp->setIsTemp(false);
			Parser::_variables.insert({ name, temp });
			return true;
		}
		if (str.find('+') != std::string::npos) {
			int indexP = value.find('+');
			std::string Left = "";
			std::string Right = "";
			for (int i = 0; i < indexP; i++) {
				Left += value[i];
			}

			for (int i = indexP+1; i < value.length(); i++) {
				Right += value[i];
			}

			Type * valLeftType = Parser::getType(Left);
			Type * valRightType = Parser::getType(Right);

			Helper::trim(Left);
			Helper::trim(Right);

			std::unordered_map<std::string, Type * >::iterator iter = Parser::_variables.find(name);

			//if changing a stored variable
			if (iter != Parser::_variables.end())
			{
				char * nameType = Helper::GetTypeName(iter->second);
				if (Helper::GetTypeName(valLeftType) != Helper::GetTypeName(valRightType)
					|| Helper::GetTypeName(valLeftType) != nameType
					|| Helper::GetTypeName(valRightType) != nameType)
				{
					TypeException e;
					throw e;
				}

				if (Helper::GetTypeName(valLeftType) == nullptr
					|| Helper::GetTypeName(valLeftType) == nullptr
					|| nameType == nullptr)
				{
					SyntaxException e;
					throw e;
				}

				//setting value variable
				else {
					if (nameType == "String")
					{
						std::string val = "\"";
						val += Helper::RemoveStr(valLeftType->toString());
						val += Helper::RemoveStr(valRightType->toString());
						val += "\"";
						((String *)iter->second)->setValue(val);
						delete valLeftType;
						delete valRightType;
						return true;
					}
					else if (nameType == "Integer")
					{
						int val;
						val = ((Integer *)valLeftType)->getValue() + ((Integer *)valRightType)->getValue();
						((Integer *)iter->second)->setValue(val);
						delete valLeftType;
						delete valRightType;
						return true;
					}
				}
			}
			//creating new var
			if (Helper::GetTypeName(valLeftType) != Helper::GetTypeName(valRightType))
			{
				TypeException e;
				throw e;
			}

			if (Helper::GetTypeName(valLeftType) == nullptr
				|| Helper::GetTypeName(valLeftType) == nullptr)
			{
				SyntaxException e;
				throw e;
			}

			else {
				if (Helper::GetTypeName(valLeftType) == "String")
				{
					std::string val = "\""; 
					val += Helper::RemoveStr(valLeftType->toString());
					val += Helper::RemoveStr(valRightType->toString());
					val	+= "\"";
					String * newType = new String(val);
					newType->setIsTemp(true);
					Parser::_variables.insert({ name, newType });
					delete valLeftType;
					delete valRightType;
					return true;
				}
				else if (Helper::GetTypeName(valLeftType) == "Integer")
				{
					int val;
					val = ((Integer *)valLeftType)->getValue() + ((Integer *)valRightType)->getValue();
					Integer * newType = new Integer(val);
					newType->setIsTemp(true);
					Parser::_variables.insert({ name, newType });
					delete valLeftType;
					delete valRightType;
					return true;
				}
			}

		}
	}
	return false;
}

Type * Parser::getVariableValue(const std::string & str)
{
	std::string string = str;
	Helper::trim(string);
	std::unordered_map<std::string, Type *>::iterator i = Parser::_variables.find(str);
	if (i != Parser::_variables.end())
	{
		return i->second;
	}
	return NULL;
}

void Parser::clean()
{
	std::unordered_map<std::string, Type *>::iterator i;
	for (i = Parser::_variables.begin(); i != Parser::_variables.end(); i++)
	{
		try 
		{
			if (List* v = dynamic_cast<List*>(i->second))
			{
				((List *)i->second)->clean();
			}
		}
		catch (...) {
		}
		delete(i->second);
	}
}


