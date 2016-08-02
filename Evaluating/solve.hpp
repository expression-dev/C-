#include <string>
#include <stack>
#include <utility>
#include <map>
#include <vector>
	
	using std::string;
	using std::stack;
	using std::pair;
	using std::vector;
	using std::map;

template <typename T>
class solve
{
private:
	expression <T> all;

	T (*Parse) (string a); 
public:
	solve (expression <T> a, T (*b) (string))
	{
		all = expression <T> (a);
		Parse = b;
	}

	pair <string, vector <int> > clean (string expr)
	{
		////std::cout << "Clean " << expr << std::endl;
		////std::cout.flush ();
		stack < pair <pair < int, int>, int > > pairs_brackets;
		stack < int > open;
		for (int i = 0 ; i < (int)expr.size () ; i ++)
		{
			if (all.isOpened (expr [i]))
			{
				open.push (i);
			}
			if (all.isClosed (expr [i]))
			{
				pairs_brackets.push ({{open.top (), i}, all.closed [expr [i]]});
				open.pop ();
			}
		}
		int last_open = 0;
		vector <int> opers;
		while (!pairs_brackets.empty ())
		{
			int opened = pairs_brackets.top ().first.first;
			int closed = pairs_brackets.top ().first.second;
			int brackets = pairs_brackets.top ().second;
			pairs_brackets.pop ();
			if (opened - last_open == 0 and closed - last_open == (int)expr.size () - 1)
			{
				expr.erase (0, 1);
				expr.erase (expr.size () - 1, 1);
				last_open = opened;
				opers.push_back (brackets);
			}
			else
			{
				break;
			}
		}
		return {expr, opers};
	}
	
	T subcalc (T a, vector <int> seq)
	{
		for (auto& x : seq)
			a = (*all (x))(a);
		return a;
	}

	T calc (string expr)
	{
    	//std::cout << expr << std::endl;
    	//std::cout.flush ();
////	auto cleaned = clean (expr);
////	expr = cleaned.first;
    	//std::cout << expr/* << " " << (cleaned.second.size () > 0)*/ << std::endl;
    	//std::cout.flush ();
////	if (expr == "" and cleaned.second.size () > 0)
////		throw "Invalid Expression!! ;@";
		if (expr == "")
		{
			return (*Parse)("0");
		}
		//std::cout << "I don\'t return 0 for " << expr << std::endl;
		//std::cout.flush ();
		int min_priority = all.number_priority, pos = -1;
		int bonux = 0;
		for (int i = 0 ; i < (int)expr.size () ; i ++)
		{
			if (all.operators.find (expr [i]) == std :: string :: npos)
			{
				std::string name = "";
				int first_open_bracket = i;
				for ( ; expr [first_open_bracket] != '(' ; first_open_bracket ++)
				{name += expr [first_open_bracket];}
				std::cout << name << std::endl;
				if (all.func.find (name) == all.func.end ())
					throw "Undefined digit, operator, function or bracket";
				else
				{
					for ( ; first_open_bracket < expr.size () and expr [first_open_bracket] == ')' ; first_open_bracket ++)
					{}
					i = first_open_bracket;
					continue;
				}
					
			}
			if (all.isOpened (expr [i]))
			{
				bonux += all (all.opened [expr [i]])->P;
			}
			else if (all.isClosed (expr [i]))
			{
				bonux -= all (all.closed [expr [i]])->P;
			}
			else if (all.isOper (expr [i]))
			{
				int curr_priority = all.oper [expr [i]]->priority + bonux;
				if (curr_priority == min_priority)
				{
					if (pos != -1 and expr [pos] == expr [i] and all [expr [pos]]->right_asociation)
					{
						pos = pos;
					}
					else
						pos = i;
				}
				else if (curr_priority < min_priority)
				{
					min_priority = curr_priority;
					pos = i;
				}
			}
			//std::cout << "ind = " << i << " ";
			//std::cout.flush ();
			//std::cout << "My curr min_priority = " << min_priority << " on pos = " << pos;
			//std::cout.flush ();
			//std::cout << " and bonux = " << bonux << "\n";
			//std::cout.flush ();
		}
		if (pos == -1) // TODO: parse parameters and solve function
		{
			std::cout << "Expr: " << expr << "\n"; std::cout.flush ();
			std::string name1 = "", name = "";
			int first_open_bracket = 0;
			for ( ; first_open_bracket < expr.size () and expr [first_open_bracket] != '(' ; first_open_bracket ++)
			{name1 += expr [first_open_bracket];}
			
			std::vector <T> params;
			for (first_open_bracket ++ ; first_open_bracket < expr.size () and expr [first_open_bracket] != ')' ; first_open_bracket ++)
			{
				if (expr [first_open_bracket] == ';')
				{
					params.push_back ((*Parse)(name.c_str ()));
					name = "";
					continue;
				}
				name += expr [first_open_bracket];
			}
			params.push_back ((*Parse)(name.c_str ()));
			std::cout << name1 << "\n"; std::cout.flush ();
			if (all.func.find (name1) == all.func.end ())
			{
				std::cout << "Ans: " << (*Parse)(name1.c_str ()) << "\n";
				std::cout.flush ();
				return (*Parse)(name1.c_str ());
			}
			T ans = (*all.func [name1]) (params);
			std::cout << "Ans: " << ans << "\n";
			std::cout.flush ();
			return ans;
		}
		//std::cout << "My curr min_priority = " << min_priority << " on pos = " << pos << "\n";
		auto cleaned = clean (expr);
		//std::cout << "\t0) " << expr << std::endl;
		//std::cout.flush ();
		expr = cleaned.first;
		vector < int > todo = cleaned.second;
		//std::cout << "\t1) " << expr << std::endl;
		//std::cout.flush ();
		if (pos == -1)
		{
			//std::cout << "1) " << expr << std::endl;
			//std::cout.flush ();
			T ans = (*Parse) (expr.c_str ());
			ans = subcalc (ans, todo);
			return ans;
		}
		else
		{
			pos -= todo.size ();
			//std::cout << "2) " << expr << " " << pos << std::endl;
			//std::cout.flush ();
			T ans = (*all.oper [expr [pos]])({calc (expr.substr (0, pos)), calc (expr.substr (pos + 1))});
			ans = subcalc (ans, todo);
			return ans;
		}
	}
};
