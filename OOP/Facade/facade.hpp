#include <map>
#include <vector>

namespace expr
{
	template <typename T>
	class function
	{
	public:
		std::string name;
		virtual T operator() (std::vector <T>) const = 0;
	};

	template <typename T>
	class bracket
	{
	public:
		char open;
		char close;
		int P;
		int M;
		virtual T operator() (T) const = 0;
	};

	template <typename T>
	class operation
	{
	public:
		int operands;
		int priority;
		char symbol;
		bool right_asociation; ////!!!! to constructor
		virtual T operator() (std::vector <T>) const = 0;
	};

	template <typename T>
	class expression
	{
	private:
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
