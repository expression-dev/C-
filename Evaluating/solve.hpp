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
    	//std::cout << "Expr: " << expr << std::endl;
		//std::cout.flush ();
		if (expr == "")
		{
			return (*Parse)("0");
		}
		int min_priority = all.number_priority, pos = -1;
		int bonux = 0;
		for (int i = 0 ; i < (int)expr.size () ; i ++)
		{
			//std::cout << "Expr: " << expr << "  Curr char: " << expr [i] << std::endl;
			//std::cout << all.operators << std::endl;
			if (all.operators.find (expr [i]) == std :: string :: npos)
			{
				std::string name = "";
				int first_open_bracket = i;
				for ( ; expr [first_open_bracket] != '(' ; first_open_bracket ++)
				{name += expr [first_open_bracket];}
				if (all.func.find (name) == all.func.end ())
					throw "Undefined digit, operator, function or bracket";
				else
				{
					for ( ; first_open_bracket < expr.size () and expr [first_open_bracket] != ')' ; first_open_bracket ++)
					{}
					//std::cout << "CHECK: " << name << " " << i << " " << first_open_bracket << " ";
					i = first_open_bracket;
					//std::cout << i << std::endl;
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
				//std::cout << "Expr: " << expr << "  Curr char: " << expr [i] << " Optimum char: " << expr [pos] << " " << min_priority << curr_priority << std::endl;
				if (curr_priority == min_priority)
				{
					if (pos != -1 and expr [pos] == expr [i] and all.oper [expr [pos]]->right_asociation)
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
		}
		if (pos == -1) // TODO: parse parameters and solve function
		{
			//std::cout << "Expr1: " << expr << "\n"; std::cout.flush ();
			std::string name1 = "", name = "";
			int first_open_bracket = 0;
			for ( ; first_open_bracket < expr.size () and expr [first_open_bracket] != '(' ; first_open_bracket ++)
			{name1 += expr [first_open_bracket];}
			
			int start = first_open_bracket + 1, br = 0;
			for (first_open_bracket ++ ; first_open_bracket < expr.size () and expr [first_open_bracket] != ')' ; first_open_bracket ++)
			{ br ++; 
				//std::cout << "char: #^&*" << expr [first_open_bracket] << " " << expr [first_open_bracket + 1] << std::endl; 
				}
			if (all.func.find (name1) == all.func.end ())
			{
				return (*Parse)(name1.c_str ());
			}
			//std::cout << "Recursive: " << start << " " << first_open_bracket << " " << br << " " << expr.substr (start, first_open_bracket - start) << std::endl;
			T ans = (*all.func [name1]) (expr.substr (start, br));
			//std::cout << "Ans: " << ans << "\n";
			//std::cout.flush ();
			return ans;
		}
		//std::cout << "Expr2: " << expr << "\n"; std::cout.flush ();
		auto cleaned = clean (expr);
		expr = cleaned.first;
		vector < int > todo = cleaned.second;
		if (pos == -1)
		{
			T ans = (*Parse) (expr.c_str ());
			ans = subcalc (ans, todo);
			return ans;
		}
		else
		{
			pos -= todo.size ();
			T ans = (*all.oper [expr [pos]])({calc (expr.substr (0, pos)), calc (expr.substr (pos + 1))});
			ans = subcalc (ans, todo);
			return ans;
		}
	}
};
