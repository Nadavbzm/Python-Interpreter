#include "Helper.h"
#include "SyntaxException.h"

bool Helper::isInteger(const std::string& s)
{
	int start = (s[0] == '-') ? 1 : 0;
	for (int i = start; i < s.size(); i++)
	{
		if (!isDigit(s[i]))
		{
			return false;
		}
	}

	return true;
}

bool Helper::isBoolean(const std::string& s)
{
	return (s == "True" || s == "False");
}


bool Helper::isString(const std::string& s)
{
	size_t end = s.size() - 1;

	if (s[0] == '\"' && end == s.find('\"', 1))
	{
		return true;
	}
	if (s[0] == '\'' && end == s.find('\'', 1))
	{
		return true;
	}

	return false;

}

bool Helper::isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

void Helper::trim(std::string &str)
{
	rtrim(str);
	ltrim(str);

}

void Helper::rtrim(std::string &str)
{
	size_t endpos = str.find_last_not_of(" \t");
	if (std::string::npos != endpos)
	{
		str = str.substr(0, endpos + 1);
	}
}

void Helper::ltrim(std::string &str)
{
	size_t startpos = str.find_first_not_of(" \t");
	if (std::string::npos != startpos)
	{
		str = str.substr(startpos);
	}
}

void Helper::removeLeadingZeros(std::string &str)
{
	size_t startpos = str.find_first_not_of("0");
	if (std::string::npos != startpos)
	{
		str = str.substr(startpos);
	}
}

bool Helper::checkString(std::string & str, char x)
{
	for (int i = 0; i < str.length(); i++)
	{
		return false;
	}
}

bool Helper::isList(std::string & str)
{
	std::string tempString = "";
	int prev = 1;
	int next = 1;
	bool startString = false;
	if(str[0] == '[' && str[str.length() - 1] == ']')
	{
		for (int i = 1; i < str.length(); i++)
		{
			if (str[i] != ',' && str[i] != ' ')
			{
				if (str[i] == '"' && !startString)
				{
					startString = true;
					for (int k = i; k < str.length() - 1 && startString; k++)
					{
						if (str[k] == '"')
						{
							if (str[k + 1] == ',' || k+1 == str.length()-1)
							{
								i = k + 1;
								startString = false;
								break;
							}
						}
					}
				}
				if (str[i] != '"')
				{
					for (int l = i; l < str.length() - 1 && str[l] != ','; l++)//get all var
					{
						tempString += str[l];
						i = l;
					}
					if (!(isInteger(tempString) || isBoolean(tempString)))
						{
							SyntaxException e;
							throw e;
						}
						tempString = "";
				}
			}
		}
		return true;
	}

	return false;
}

char * Helper::GetTypeName(Type * x)
{
	if (Helper::isInteger(x->toString()))
	{
		return "Integer";
	}

	if (Helper::isString(x->toString()))
	{
		return "String";
	}

	if (Helper::isBoolean(x->toString()))
	{
		return "Boolean";
	}
	return nullptr;
}

std::string Helper::RemoveStr(std::string str)
{
	std::string t = "";
	for (int i = 1; i != str.length()-1; i++)
	{
		t += str[i];
	}
	return t.c_str();
}


bool Helper::isLowerLetter(char c)
{
	return (c >= 'a' && c <= 'z');
}

bool Helper::isUpperLetter(char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool Helper::isLetter(char c)
{
	return (isLowerLetter(c) || isUpperLetter(c));
}

bool Helper::isUnderscore(char c)
{
	return ('_' == c);
}

