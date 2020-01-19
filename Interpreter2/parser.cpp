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
			i = Parser::_variables.find(name);
			i->second =  temp;
			return true;
		}

		//if addition in value
		if (str.find('+') != std::string::npos) 
		{
			int count = 0;
			for (int i = 0; i < value.length(); i++)
			{
				if (value[i] == '+')
				{
					count++;
				}
			}
			
			std::vector<std::pair<std::string, Type *>> TempValues;
			std::unordered_map<std::string, Type * >::iterator iter;
			Type * valLeftType = nullptr;

			int indexP = 0;
			for (int k = 0; k < count+1; k++)
			{
				//Counting number of Slicing
				indexP = value.find('+');
				std::string Left = "";
				if (indexP == std::string::npos)
				{
					indexP = value.length();
				}
				for (int i = 0; i < indexP; i++) { Left += value[i]; }
				Helper::trim(Left);

				//Checking if Left Value is a known varible
				iter = Parser::_variables.find(Left);
				if (iter != Parser::_variables.end())
				{
					valLeftType = iter->second->copy();
					TempValues.push_back({ Left,valLeftType });
				}

				//Getting value of Left
				else
				{
					valLeftType = Parser::getType(Left);
					if (valLeftType == NULL)
					{
						for (int l = 0; l < TempValues.size(); l++)
						{
							delete TempValues[l].second;
						}
						//Syntx Error - not known type
						SyntaxException e;
						throw e;
					}

					TempValues.push_back({ Left, valLeftType });
				}
				
				std::string newValueLeft = "";
				for (int i = indexP+1; i < value.length(); i++)
				{
					newValueLeft += value[i];
				}
				value = newValueLeft;
			}

				iter = Parser::_variables.find(name);
				
				//if changing a stored variable
				if (iter != Parser::_variables.end())
				{
					//setting value variable
						if (Helper::GetTypeName(TempValues[0].second) == "String")
						{
							for (int m = 0; m < TempValues.size(); m++)
							{
								if (Helper::GetTypeName(TempValues[m].second) != "String")
								{
									for (int l = 0; l < TempValues.size(); l++)
									{
										delete TempValues[l].second;
									}
									TypeException e;
									throw e;
								}
							}
							std::string val = "\"";
							for (int m = 0; m < TempValues.size(); m++)
							{
								val += Helper::RemoveStr(TempValues[m].second->toString());
							}
							val += "\"";
							try {
								if (List* v = dynamic_cast<List*>(iter->second)) {
									((List *)iter->second)->clean();
								}
							}
							catch (...) {
								delete iter->second;
							}
							iter->second = new String(val);
							iter->second->setIsTemp(false);
							for (int l = 0; l < TempValues.size(); l++)
							{
								delete TempValues[l].second;
							}
							return true;
						}
						if (Helper::GetTypeName(TempValues[0].second) == "Integer")
						{
							for (int m = 0; m < TempValues.size(); m++)
							{
								if (Helper::GetTypeName(TempValues[m].second) != "Integer")
								{
									for (int l = 0; l < TempValues.size(); l++)
									{
										delete TempValues[l].second;
									}
									TypeException e;
									throw e;
								}
							}
							int val = 0;
							for (int m = 0; m < TempValues.size(); m++)
							{
								val += ((Integer *)TempValues[m].second)->getValue();
							}
							try {
								if (List* v = dynamic_cast<List*>(iter->second)) {
									((List *)iter->second)->clean();
								}
							}
							catch (...) {
								delete iter->second;
							}
							iter->second = new Integer(val);
							iter->second->setIsTemp(false);
							for (int l = 0; l < TempValues.size(); l++)
							{
								delete TempValues[l].second;
							}
							return true;
						}
				}
				//creating new var
				if (Helper::GetTypeName(TempValues[0].second) == "String")
				{
					for (int m = 1; m < TempValues.size(); m++)
					{
						if (Helper::GetTypeName(TempValues[m].second) != "String")
						{
							for (int l = 0; l < TempValues.size(); l++)
							{
								delete TempValues[l].second;
							}
							TypeException e;
							throw e;
						}
					}
						std::string val = "\"";
						for (int m = 0; m < TempValues.size(); m++)
						{
							val += Helper::RemoveStr(((String *)TempValues[m].second)->toString());
						}
						val += "\"";
						String * newType = new String(val);
						newType->setIsTemp(false);
						Parser::_variables.insert({ name, newType });
						for (int l = 0; l < TempValues.size(); l++)
						{
							delete TempValues[l].second;
						}
						return true;
				}
				else if (Helper::GetTypeName(TempValues[0].second) == "Integer")
				{
					for (int m = 0; m < TempValues.size(); m++)
					{
						if (Helper::GetTypeName(TempValues[m].second) != "Integer")
						{
							for (int l = 0; l < TempValues.size(); l++)
							{
								delete TempValues[l].second;
							}
							TypeException e;
							throw e;
						}
					}
					int val = 0;
					for (int m = 0; m < TempValues.size(); m++)
					{
						val += (((Integer *)TempValues[m].second)->getValue());
					}
					Integer * newType = new Integer(val);
					newType->setIsTemp(false);
					Parser::_variables.insert({ name, newType });
					for (int l = 0; l < TempValues.size(); l++)
					{
						delete TempValues[l].second;
					}
					return true;
				}		

		}

		//Minus Operation
		if (str.find('-') != std::string::npos)
		{
			int count = 0;
			for (int i = 0; i < value.length(); i++)
			{
				if (value[i] == '-')
				{
					count++;
				}
			}

			std::vector<std::pair<std::string, Type *>> TempValues;
			std::unordered_map<std::string, Type * >::iterator iter;
			Type * valLeftType = nullptr;

			int indexP = 0;
			for (int k = 0; k < count; k++)
			{
				//Counting number of Slicing
				indexP = value.find('-');
				std::string Left = "";
				if (indexP == std::string::npos)
				{
					indexP = value.length();
				}
				for (int i = 0; i < indexP; i++) { Left += value[i]; }
				Helper::trim(Left);

				//Checking if Left Value is a known varible
				iter = Parser::_variables.find(Left);
				if (iter != Parser::_variables.end())
				{
					valLeftType = iter->second->copy();
					TempValues.push_back({ Left,valLeftType });
				}

				//Getting value of Left
				else
				{
					valLeftType = Parser::getType(Left);
					if (valLeftType == NULL)
					{
						for (int l = 0; l < TempValues.size(); l++)
						{
							delete TempValues[l].second;
						}
						//Syntx Error - not known type
						SyntaxException e;
						throw e;
					}

					TempValues.push_back({ Left, valLeftType });
				}

				std::string newValueLeft = "";
				for (int i = indexP + 1; i < value.length(); i++)
				{
					newValueLeft += value[i];
				}
				value = newValueLeft;
			}

			iter = Parser::_variables.find(name);

			//if changing a stored variable
			if (iter != Parser::_variables.end())
			{
				//setting value variable
				if (Helper::GetTypeName(TempValues[0].second) == "Integer")
				{
					for (int m = 0; m < TempValues.size(); m++)
					{
						if (Helper::GetTypeName(TempValues[m].second) != "Integer")
						{
							for (int l = 0; l < TempValues.size(); l++)
							{
								delete TempValues[l].second;
							}
							TypeException e;
							throw e;
						}
					}
					int val = (((Integer *)TempValues[0].second)->getValue());
					for (int m = 1; m < TempValues.size(); m++)
					{
						val -= ((Integer *)TempValues[m].second)->getValue();
					}
					try {
						if (List* v = dynamic_cast<List*>(iter->second)) {
							((List *)iter->second)->clean();
						}
					}
					catch (...) {
						delete iter->second;
					}
					iter->second = new Integer(val);
					iter->second->setIsTemp(false);
					for (int l = 0; l < TempValues.size(); l++)
					{
						delete TempValues[l].second;
					}
					return true;
				}
			}
			//creating new var
			if (Helper::GetTypeName(TempValues[0].second) == "Integer")
			{
				for (int m = 0; m < TempValues.size(); m++)
				{
					if (Helper::GetTypeName(TempValues[m].second) != "Integer")
					{
						for (int l = 0; l < TempValues.size(); l++)
						{
							delete TempValues[l].second;
						}
						TypeException e;
						throw e;
					}
				}
				int val = (((Integer *)TempValues[0].second)->getValue());
				for (int m = 1; m < TempValues.size(); m++)
				{
					val -= (((Integer *)TempValues[m].second)->getValue());
				}
				Integer * newType = new Integer(val);
				newType->setIsTemp(false);
				Parser::_variables.insert({ name, newType });
				for (int l = 0; l < TempValues.size(); l++)
				{
					delete TempValues[l].second;
				}
				return true;
			}
		}
		//* Operation
		if (str.find('*') != std::string::npos)
		{
			int count = 0;
			for (int i = 0; i < value.length(); i++)
			{
				if (value[i] == '*')
				{
					count++;
				}
			}

			Type * valLeftType = nullptr;
			std::vector<std::pair<std::string, Type *>> TempValues;
			std::unordered_map<std::string, Type * >::iterator iter;
			int indexP = 0;
			for (int k = 0; k < count+1; k++)
			{
				//Counting number of Slicing
				indexP = value.find('*');
				std::string Left = "";
				if (indexP == std::string::npos)
				{
					indexP = value.length();
				}
				for (int i = 0; i < indexP; i++) { Left += value[i]; }
				Helper::trim(Left);

				//Checking if Left Value is a known varible
				iter = Parser::_variables.find(Left);
				if (iter != Parser::_variables.end())
				{
					valLeftType = iter->second->copy();
					TempValues.push_back({ Left,valLeftType });
				}

				//Getting value of Left
				else
				{
					valLeftType = Parser::getType(Left);
					if (valLeftType == NULL)
					{
						for (int l = 0; l < TempValues.size(); l++)
						{
							delete TempValues[l].second;
						}
						//Syntx Error - not known type
						SyntaxException e;
						throw e;
					}

					TempValues.push_back({ Left, valLeftType });
				}

				std::string newValueLeft = "";
				for (int i = indexP + 1; i < value.length(); i++)
				{
					newValueLeft += value[i];
				}
				value = newValueLeft;
			}

			iter = Parser::_variables.find(name);

			//if changing a stored variable
			if (iter != Parser::_variables.end())
			{
				//setting value of stored variable
				int val = 1;
				if (Helper::GetTypeName(TempValues[0].second) == "Integer")
				{
					for (int m = 0; m < TempValues.size(); m++)
					{
						if (Helper::GetTypeName(TempValues[m].second) != "Integer")
						{
							if (Helper::GetTypeName(TempValues[m].second) == "String" && m == TempValues.size() - 1)
							{
								std::string StringVal = "\"";
								for (int i = 0; i < val && i < MAX_MUL_STR; i++)
								{
									StringVal += Helper::RemoveStr(TempValues[m].second->toString());
								}
								StringVal += "\"";
								try {
									if (List* v = dynamic_cast<List*>(iter->second)) {
										((List *)iter->second)->clean();
									}
								}
								catch (...) {
									delete iter->second;
								}
								iter->second = new String(StringVal);
								iter->second->setIsTemp(false);
								for (int l = 0; l < TempValues.size(); l++)
								{
									delete TempValues[l].second;
								}
								return true;
							}
							for (int l = 0; l < TempValues.size(); l++)
							{
								delete TempValues[l].second;
							}
							TypeException e;
							throw e;
						}

						val *= ((Integer *)(TempValues[m].second))->getValue();
					}
					try {
						if (List* v = dynamic_cast<List*>(iter->second)) {
							((List *)iter->second)->clean();
						}
					}
					catch (...) {
						delete iter->second;
					}
					iter->second = new Integer(val);
					iter->second->setIsTemp(false);
					for (int l = 0; l < TempValues.size(); l++)
					{
						delete TempValues[l].second;
					}
					return true;
				}

				//other
				if (Helper::GetTypeName(TempValues[0].second) == "String")
				{
					int val = 1;
					std::string StringVal = "\"";
					for (int m = 1; m < TempValues.size() && m < MAX_MUL_STR; m++)
					{
						if (Helper::GetTypeName(TempValues[m].second) != "Integer")
						{
							for (int l = 0; l < TempValues.size(); l++)
							{
								delete TempValues[l].second;
							}
							TypeException e;
							throw e;
						}

						val *= ((Integer *)(TempValues[m].second))->getValue();
					}
					for (int i = 0; i < val && val < MAX_MUL_STR; i++)
					{
						StringVal += Helper::RemoveStr(TempValues[0].second->toString());
					}
					StringVal += "\"";
					try {
						if (List* v = dynamic_cast<List*>(iter->second)) {
							((List *)iter->second)->clean();
						}
					}
					catch (...) {
						delete iter->second;
					}
					iter->second = new String(StringVal);
					iter->second->setIsTemp(false);
					for (int l = 0; l < TempValues.size(); l++)
					{
						delete TempValues[l].second;
					}
					return true;
				}
			}
			//setting creating new variable
			else {
				int val = 1;
				if (Helper::GetTypeName(TempValues[0].second) == "Integer")
				{
					for (int m = 0; m < TempValues.size(); m++)
					{
						if (Helper::GetTypeName(TempValues[m].second) != "Integer")
						{
							if (Helper::GetTypeName(TempValues[m].second) == "String" && m == TempValues.size() - 1)
							{
								std::string StringVal = "\"";
								for (int i = 0; i < val && i < MAX_MUL_STR; i++)
								{
									StringVal += Helper::RemoveStr(TempValues[m].second->toString());
								}
								StringVal += "\"";
								Type * newType = new String(StringVal);
								newType->setIsTemp(false);
								Parser::_variables.insert({ name, newType });
								for (int l = 0; l < TempValues.size(); l++)
								{
									delete TempValues[l].second;
								}
								return true;
							}
							for (int l = 0; l < TempValues.size(); l++)
							{
								delete TempValues[l].second;
							}
							TypeException e;
							throw e;
						}

						val *= ((Integer *)(TempValues[m].second))->getValue();
					}
					Type * newType = new Integer(val);
					newType->setIsTemp(false);
					Parser::_variables.insert({ name, newType });
					for (int l = 0; l < TempValues.size(); l++)
					{
						delete TempValues[l].second;
					}
					return true;
				}

				//other
				if (Helper::GetTypeName(TempValues[0].second) == "String")
				{
					int val = 0;
					std::string StringVal = "\"";
					for (int m = 1; m < TempValues.size() && m < MAX_MUL_STR; m++)
					{
						if (Helper::GetTypeName(TempValues[m].second) != "Integer")
						{
							for (int l = 0; l < TempValues.size(); l++)
							{
								delete TempValues[l].second;
							}
							TypeException e;
							throw e;
						}

						val *= ((Integer *)(TempValues[m].second))->getValue();
					}
					for (int i = 0; i < val && val < MAX_MUL_STR; i++)
					{
						StringVal += Helper::RemoveStr(TempValues[0].second->toString());
					}
					StringVal += "\"";
					
					Type * newType = new String(StringVal);
					newType->setIsTemp(false);
					Parser::_variables.insert({ name, newType });
					for (int l = 0; l < TempValues.size(); l++)
					{
						delete TempValues[l].second;
					}
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


