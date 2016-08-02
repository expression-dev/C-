#include <vector>
#include <algorithm>

using std::vector;
using std::move;

template <typename T>
struct Polynom
{
private:
	vector <T> k;
public:
	Polynom (vector <T> k1)
	{
		std::reverse (k1.begin (), k1.end ());
		k = move (k1);
	}
};

Polynom operator + (Polynom a, Polynom b)
{
	Polynom c;
	if (a.size () < b.size ()) swap (a, b);

	c = a;
	for (size_t i = 0 ; i < b.size () and i < c.size () ; i ++)
		c [i] += b [i];
	return move (c);
}

Polynom operator - (Polynom a, Polynom b)
{
	Polynom c;
	if (a.size () < b.size ()) swap (a, b);

	c = a;
	for (size_t i = 0 ; i < b.size () and i < c.size () ; i ++)
		c [i] += b [i];
	return move (c);
}
