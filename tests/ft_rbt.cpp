#include <stdlib.h>
#include <string>

/* # if 1
 #include <utility>
 #include <map>
 typedef std::map<int, int> object;
#else
 typedef ft::RedBlackTree<int, int> object;
#endif */

#include "../includes/RedBlackTree.hpp"
#include "../includes/vector.hpp"
#include "../includes/type_traits.hpp"
#include <map>

template <class InputIterator>
void
iter_print( InputIterator __first, InputIterator __last )
{
	while (__first != __last)
	{
		std::cout << __first->first << '\t' << __first->second << '\n';
		__first++;
	}
}

template <class InputIterator>
void
iter_print_reverse( InputIterator __first, InputIterator __last )
{
	while (__last != __first)
	{
		std::cout << __last->first << '\t' << __last->second << '\n';
		__last--;
	}
}

/** TODO: Test erase functions */

typedef ft::RedBlackTree<const int, int>	object;
//typedef std::map<const int, int> object;

int main( void )
{
	{
		object a, b;
		//std::map<int, int> x;
		a.insert(ft::make_pair(1, 1));
		a.insert(ft::make_pair(2, 2));

		b.insert(ft::make_pair(3, 3));
		b.insert(ft::make_pair(4, 4));

		object::iterator beg = a.begin();
		object::iterator end = b.end();

		a.swap(b);

		while (beg != end)
		{
			std::cout << beg->first << ' ' << beg->second << '\n';
			beg++;
		}
	}

	{
		srand(time(NULL));
		object	x;
		std::map<int, int>	y;

		for (int i = 0; i < 16; i++)
		{
			int num = rand();
			x.insert(ft::make_pair(num, i));
			y.insert(std::make_pair(num, i));
		}
		//x.print();
		iter_print_reverse(x.begin(), --x.end());
		std::cout << "     " << '\n';
		iter_print_reverse(y.begin(), --y.end());
		std::cout << "end" << '\n';
	}

	{
		object m;

		std::cout << (m.begin() == m.end() ? "true" : "false") << '\n';

		m.insert(ft::make_pair(1, 0));
		m.insert(ft::make_pair(2, 0));
		m.insert(ft::make_pair(3, 0));

		object::const_reverse_iterator it = m.rbegin();
		//object::reverse_iterator it2 = it;

		for (; it != m.rend(); it++)
		{
			//*it = ft::make_pair(42, 42);
			//it->second = 42;
			std::cout << it->first << '\n';
			//std::cout << it->first << " " << it->second << '\n';
		}
		it--;
		std::cout << it->first << '\n';

		//std::cout << typeid (std::allocator<std::pair<int, int>*>).name() << '\n';

		// for (int i = 0; i < 16; i++)
		// 	x.insert(ft::make_pair(i, 100 + i));
		
		//*it = ft::make_pair(0, 0);
		// std::cout << it->first << '\n';
		// it->second = 420;
		// std::cout << it->second << '\n';
	}
	return (0);
}
