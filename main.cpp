#include "OOP/Facade/facade.hpp"

#include <iostream>
#include <string>

using namespace expr;
#include "Evaluating/solve.hpp"

#include "other/transform.hpp"
#include "other/parser.hpp"

#include <fstream>
#include <sstream>

int main ()
{
	expression <int> expr;
	#include "other/reader.cpp"
	std::cout << (*expr.func ["sqrt"])("1,2");
	solve <int> solver (expr, parser);
	std::string to_solve, in;

	getline (std::cin, in);
	for (auto& x : in)
		if (x != ' ')
			to_solve += x;
	while (std::cin)
	{
		try
		{
			std::cout << "Calculated: " << to_solve << " = " << solver.calc (to_solve) << std::endl;
		}
		catch (const char* asdf)
		{
			std::cout << "\n\nError: " << asdf << std::endl;
		}
		std::cout << "😕 😭 \n";
		to_solve = "";
		getline (std::cin, in);
		for (auto& x : in)
			if (x != ' ')
				to_solve += x;
	}
}
