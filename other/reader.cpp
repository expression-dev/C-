	
{
		std::ifstream in ("in");
		std::string curr_line;
		std::string def;
		int N = 0;
	while (!in.eof())
	{
		Start:
		{
			getline (in, curr_line);
			def = "";
			int i = 0;
			for (i = 0 ; curr_line [i] != ' ' and curr_line [i] != '[' ; i ++)
				def += curr_line [i];
			std::cout << def << std::endl;
			if (def == "function")
			{
				string code = "template <typename T> T f (std::string str)\n{\n ";
				string name = "";
				for (i ++ ; curr_line [i] != '(' ; i ++) { if (curr_line [i] != ' ')
					name += curr_line[i];}
				for ( i ++ ; curr_line [i] != ')' ; i ++)
				{
				}
				while (!in.eof ())
				{
					getline (in, curr_line);
					if (curr_line == "end")
					{
						code += "}";
						break;
					}
					else
						code += curr_line + "\n";
				}
expr.addFunction (new function <int> (name, N));
				std::cout << name << ": \n" << code << std::endl;
				std::ofstream out ("/tmp/new_op_fun_br.cpp");
				out << code << "\n";
				out.close ();
				std::stringstream ss;
				ss << "g++ -O2 -Wall -Wextra -std=c++11 other/base0.cpp -o exec/" << N++ << ".exe";
				system (ss.str ().c_str ());
				//std::cout << "------------------------------" << std::endl;
				goto Start;
			}
			else if (def == "bracket")
			{
				//std::cout << "Again" << std::endl;
				int priority = 0;
				std::string pair;
				std::string code = "template <typename T> T f (T ";
				for ( ; curr_line [i] != '[' ; i ++) {}
				for (i ++ ; curr_line [i] != ']' ; i ++) { priority = priority * 10 + (curr_line [i] - '0');}
				for (i ++ ; pair.size () < 2 ; i ++) 
					if (curr_line [i] != ' ') 
						pair += curr_line [i]; 

				for ( ; curr_line [i] != '(' ; i ++) {}
				for ( i ++ ; curr_line [i] != ')' ; i ++) {code += curr_line [i];}
				code += ")\n{\n";
				while (!in.eof ())
				{
					getline (in, curr_line);
					if (curr_line == "end")
					{
						code += "}";
						break;
					}
					else
						code += curr_line + "\n";
				}
expr.addBrackets (new bracket <int> (pair [0], pair [1], priority, N));
				std::cout << code << std::endl << "Pair: " << pair << std::endl << "Priority: " << priority << std::endl;
				std::ofstream out ("/tmp/new_op_fun_br.cpp");
				out << code << "\n";
				out.close ();
				std::stringstream ss;
				ss << "g++ -O2 -Wall -Wextra -std=c++11 other/base1.cpp -o exec/" << N++ << ".exe";
				system (ss.str ().c_str ());
				//std::cout << "------------------------------" << std::endl;
				goto Start;
			}
			else if (def == "operator")
			{
				//std::cout << "No" << std::endl;
				int priority = 0;
				bool right_asociation = 0;
				std::string pair;
				std::string code = "template <typename T> T f (T ";
				for ( ; curr_line [i] != '[' ; i ++) {}
				for (i ++ ; curr_line [i] != ']' ; i ++) { priority = priority * 10 + (curr_line [i] - '0');}
				for ( ; curr_line [i] != '[' ; i ++) {}
				right_asociation = (curr_line [i + 1] - '0');
				for ( ; curr_line [i] != ']' ; i ++) { }
				for (i ++ ; pair.size () < 1 ; i ++) 
					if (curr_line [i] != ' ') 
						pair += curr_line [i]; 

				for ( ; curr_line [i] != '(' ; i ++) {}
				for ( i ++ ; curr_line [i] != ',' ; i ++) {code += curr_line [i];}
				code += ", T ";
				for ( i ++ ; curr_line [i] != ')' ; i ++) {code += curr_line [i];}
				code += ")\n{\n";
				while (!in.eof ())
				{
					getline (in, curr_line);
					if (curr_line == "end")
					{
						code += "}";
						break;
					}
					else
						code += curr_line + "\n";
				}
expr.addOperation (new operation <int> (pair [0], priority, N, right_asociation));
				std::cout << code << std::endl << "Symbol: " << pair << std::endl << "Priority: " << priority << std::endl;
				std::ofstream out ("/tmp/new_op_fun_br.cpp");
				out << code << "\n";
				out.close ();
				std::stringstream ss;
				ss << "g++ -O2 -Wall -Wextra -std=c++11 other/base2.cpp -o exec/" << N++ << ".exe";
				system (ss.str ().c_str ());
				//std::cout << "------------------------------" << std::endl;
				goto Start;
			}
		}
	}
}
