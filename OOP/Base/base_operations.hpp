#include <cmath>
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
		bool right_asociation;
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
			if (v.size () < 2) //binary operator
				throw "Bad Arguments! ;(";
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
			if (v.size () < 2) //binary operator
				throw "Bad Arguments! ;(";
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
}
