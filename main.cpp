#include "OOP/Facade/facade.hpp"

#include <iostream>
#include <string>

using namespace expr;
#include "Evaluating/solve.hpp"

#include "other/transform.hpp"
#include "other/parser.hpp"

#include <fstream>
#include <sstream>
int N = 0;

std::string transform (std::string str)
{
	std::string ans;
	bool is_name = false;
	for (int i = 0 ; i < str.size () ; i ++)
	{
		std::cout << is_name << " " << str [i] << " " << str [i + 1] << " " << ans << std::endl;
		if (('a' <= str [i] and str [i] <= 'z') or ('A' <= str [i] and str [i] <= 'Z'))
			is_name = true;
		else if ('0' <= str [i] and str [i] <= '9')
			is_name = is_name;
		else if (is_name and str [i] != '(')
		{
			ans += "()";
			is_name = false;
		}
		else if (is_name and str [i] == '(')
		{
			is_name = false;
		}
		ans += str [i];
	}
	if (is_name)
		ans += "()";
	return ans;
}

int main ()
{
	expression <int> expr;
	#include "other/reader1.cpp"
	solve <int> solver = solve <int> (expr, parser);
	std::string to_solve, in;

	getline (std::cin, in);
	for (auto& x : in)
		if (x != ' ')
			to_solve += x;
	while (std::cin)
	{
		if (in == "I want more operations!")
		{
			system ("$EDITOR in");
			#include "other/reader2.cpp"
			solver = solve <int> (expr, parser);
			getline (std::cin, in);
			for (auto& x : in)
				if (x != ' ')
					to_solve += x;
		}
		else if (in.substr (0, 4) == "calc")
		{
			to_solve = in.substr (5);
			try
			{
				std::string to_solve1 = transform (to_solve);
				std::cout << "Calculated: " << to_solve << " = " << solver.calc (to_solve1) << std::endl;
			}
			catch (const char* asdf)
			{
				std::cout << "\n\nError: " << asdf << std::endl;
			}
		}
		to_solve = "";
		getline (std::cin, in);
		for (auto& x : in)
			if (x != ' ')
				to_solve += x;
	}
}
