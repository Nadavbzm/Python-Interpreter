#include "type.h"
#include "InterperterException.h"
#include "parser.h"
#include <iostream>

#define WELCOME "Welcome to Python Interperter version 1.0 by "
#define YOUR_NAME "[Nadav Ben Tzur Montell]"


int main(int argc, char **argv)
{
	std::cout << WELCOME << YOUR_NAME << std::endl;

	std::string input_string;

	// get new command from user
	std::cout << ">>> ";
	std::getline(std::cin, input_string);

	while (input_string != "quit()")
	{
		try
		{
			// prasing command
			Type * t = Parser::parseString(input_string);
			if (t->isPrintable())
			{
				std::cout << t->toString() << std::endl;
			}
			if (t->isTemp())
			{
				delete(t);
				//std::cout << "\nVariable is temporary - freed space\n";
			}
		}
		catch (InterperterException& e)
		{
			std::cout << e.what() << std::endl;
		}
		

		// get new command from user
		std::cout << ">>> ";
		std::getline(std::cin, input_string);
	}
	//Cleaning Allocated Memory
	Parser::clean();
	return 0;
}


