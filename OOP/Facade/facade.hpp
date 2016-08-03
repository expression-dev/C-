#include <map>
#include <vector>
#include <sstream>

namespace expr
{
	template <typename T>
	class operation
	{
	public:
		int num;
		int priority;
		char symbol;
		bool right_asociation; ////!!!! to constructor
		T operator() (std::vector <T> v) const
		{
			if (v.size () < 2) //binary operator
				throw "Bad Arguments! ;(";
			std::stringstream ss;
			ss << "echo \"" << v [0] << " " << v [1] << "\" | ./exec/" << num << ".exe > /tmp/out\n";
			system (ss.str ().c_str ());
			std::ifstream in ("/tmp/out");
			T ans;
			in >> ans;
			return ans;
		}
		operation (char s, int p, int num, bool right_asociation)
		{
			this->num = num;
			this->right_asociation = right_asociation;
			this->symbol = s;
			this->priority = p;
		}
	};

	template <typename T>
	class bracket
	{
	public:
		int num;
		char open;
		char close;
		int P;
		int M;
		T operator() (T a) const
		{
			std::stringstream ss;
			ss << "echo \"" << a << "\" | ./exec/" << num << ".exe > /tmp/out\n";
			system (ss.str ().c_str ());
			std::ifstream in ("/tmp/out");
			T ans;
			in >> ans;
			return ans;
		}
		bracket (char open, char close, int priority, int num)
		{
			this->num = num;
			this->open = open;
			this->close = close;
			this->P = priority;
			this->M = -priority;
		}
	};
	
	template <typename T>
	class function
	{
	public:
		int num;
		std::string name;
		T operator() (std::string a) const
		{
			std::stringstream ss;
			ss << "echo \"" << a << "\" | ./exec/" << num << ".exe > /tmp/out\n";
			system (ss.str ().c_str ());
			std::ifstream in ("/tmp/out");
			T ans;
			in >> ans;
			return ans;
		}
		function (std::string name, int num)
		{
			this->num = num;
			this->name = name;
		}
	};
	//pavel.panov@gmail.com
	
	template <typename T>
	class expression
	{
	public:
		std::string digits;
		std::string operators;
		int number_priority = 0;
		std::vector <  function <T>* >  functions;
		std::vector < operation <T>* > operations;
		std::vector <   bracket <T>* >   brackets;
		std::map <char, operation <T>* > oper;
		std::map <std::string, function <T>* > func;
		std::map <char, int > opened;
		std::map <char, int > closed;
		expression (const int a = 1e9, std::string digits = "0123456789")
		{
			number_priority = a;
			this->digits = digits;
			this->operators = digits;
		}
		void addBrackets (bracket <T>* b)
		{
			opened [b->open] = brackets.size ();
			closed [b->close] = brackets.size ();
			brackets.push_back (b);
			operators += b->open;
			operators += b->close;
		}
		void addFunction (function <T>* f)
		{
			func [f->name] = f;
			functions.push_back (f);
		}
		void addOperation (operation <T>* op)
		{
			oper [op->symbol] = op;
			operations.push_back (op);
			operators += op->symbol;
		}
		const operation <T>* operator [] (std::size_t ind)
		{
			return (operations [ind]);
		}
		const bracket <T>* operator () (std::size_t ind)
		{
			return (brackets [ind]);
		}
		bool isClosed (char a)
		{
			return closed.find (a) != closed.end ();
		}
		bool isOpened (char a)
		{
			return opened.find (a) != opened.end ();
		}
		bool isBracket (char a)
		{
			return opened.find (a) != opened.end () or closed.find (a) != closed.end ();
		}
		bool isOper (char a)
		{
			return oper.find (a) != oper.end ();
		}
	};
}
