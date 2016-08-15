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
	system ("echo \"<!DOCTYPE html>\n<title>Expression visualizatior</title> <script type=\"text/javascript\" async src=\"https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=AM_CHTML\"></script>\" > interface/index.html");
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
		if (in == "No" or in == "end")
		{
			break;
		}
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
		else if (to_solve [to_solve.size () - 1] == '\'')
		{
			try
			{
				std::stringstream ss;
				ss << "echo \"<big>Simplified: <big><big>\\`" << to_solve.substr (4) << " = " << solver.prim (to_solve.substr (5, to_solve.size () - 7)) << "\\` </big></big></big> <br><hr>\" >> interface/index.html\n";
				std::cout << ss.str () << "\n";
				system (ss.str ().c_str ());
			}
			catch (const char* asdf)
			{
				std::cout << "\n\nError: " << asdf << std::endl;
			}
		}
		else if (in.substr (0, 4) == "calc")
		{
			to_solve = in.substr (5);
			try
			{
				std::string to_solve1 = transform (to_solve);
				std::stringstream ss;
				ss << "echo \"<big>Calculated: <big><big>\\`" << to_solve << " = " << solver.calc (to_solve1) << "\\` </big></big></big> <br><hr>\" >> interface/index.html\n";
				std::cout << ss.str () << "\n";
				system (ss.str ().c_str ());
			}
			catch (const char* asdf)
			{
				std::cout << "\n\nError: " << asdf << std::endl;
			}
		}
		else if (in.substr (0, 3) == "set")
		{
			int i;
			for (i = 5 ; i < in.size () and in [i] != ' ' ; i ++) {}
			string var_name = in.substr (4, i - 4);
			to_solve = in.substr (i + 1);
			try
			{
				std::string to_solve1 = transform (to_solve);
				int vali = solver.calc (to_solve1);
				std::stringstream val;
				val << vali; 
				{
					string code = "template <typename T> T f ()\n{\n\treturn " + val.str () + ";\n}";
					expr.addFunction (new function <int> (var_name, N));
					solver = solve <int> (expr, parser);
					std::ofstream out ("/tmp/new_op_fun_br.cpp");
					out << code << "\n";
					out.close ();
					std::stringstream ss;
					ss << "g++ -O2 -std=c++11 other/base3.cpp -o exec/" << N++ << ".exe";
					system (ss.str ().c_str ());
				}
				std::stringstream ss;
				ss << "echo \"<big>Set <big><big>\\`" + var_name + " = " << to_solve << " = " << vali << "\\` </big></big></big> <br><hr>\" >> interface/index.html\n";
				std::cout << ss.str () << "\n";
				system (ss.str ().c_str ());
			}
			catch (const char* asdf)
			{
				std::cout << "\n\nError: " << asdf << std::endl;
			}
		}

		to_solve = "";
		std::cout << "Next?\n";
		getline (std::cin, in);
		for (auto& x : in)
			if (x != ' ')
				to_solve += x;
	}
}
