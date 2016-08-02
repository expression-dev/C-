#include "OOP/Facade/facade.hpp"
#include "OOP/Base/base_operations.hpp"

#include <iostream>
#include <string>

using namespace expr;
#include "Evaluating/solve.hpp"

string Transform (string expr)
{
	if (expr [0] == '|')
		expr [0] = '{';
	for (int i = 1 ; i < (int)expr.size () ; i ++)
	{
		if (expr [i] == '|')
		{
			switch (expr [i - 1])
			{
				case '+': expr [i] = '{'; break;
				case '-': expr [i] = '{'; break;
				case '*': expr [i] = '{'; break;
				case '/': expr [i] = '{'; break;
				case '^': expr [i] = '{'; break;
				case '~': expr [i] = '{'; break;
				case '>': expr [i] = '{'; break;
				case '<': expr [i] = '{'; break;
				case '(': expr [i] = '{'; break;
				case '|': expr [i] = '{'; break;
				default:  expr [i] = '}';
			}
		}
	}
	return expr;
}

int parser (std::string a)
{
	return atoi (a.c_str ());
}

int main ()
{
	expression <int> expr;
	expr.number_priority = 1000000;
	expr.addOperation (new plus_type <int> ());
	expr.addOperation (new minus_type <int> ());
	expr.addOperation (new mul_type <int> ());
	expr.addOperation (new div_type <int> ());
	expr.addOperation (new negative_type <int> ());
	expr.addOperation (new power_type <int> ());
	expr.addBrackets  (new brackets_type <int> ());
	expr.addBrackets  (new module_type <int> ());
	expr.addBrackets  (new sqrt_type <int> ());
	expr.addFunction  (new sqrt2_type <int> ());
	solve <int> solver (expr, parser);
	std::string to_solve;

	//to_solve = "({1*(2-3)}+{7-9})/{6/6-7*0+9-10+2}";
		std::cin >> to_solve; 
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
		std::cin >> to_solve; 
	}
}
