#include <map>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <iterator>
#include <string>
#include "../includes/RedBlackTree.hpp"
#include "../includes/vector.hpp"
#include "../includes/type_traits.hpp"
#include <list>

template <class InputIterator>
void
iter_print( InputIterator __first, InputIterator __last )
{
	int i = 0;

	while (__first != __last)
	{
		std::cout << i << '\t' << __first->first << '\t' << __first->second << '\n';
		__first++;
		i++;
	}
}

/** TODO: Test erase functions */

int main( void )
{
	ft::RedBlackTree<int, int> a, b;

	a.insert(ft::make_pair(1, 1));
	a.insert(ft::make_pair(2, 2));

	b.insert(ft::make_pair(3, 3));
	b.insert(ft::make_pair(4, 4));

	ft::RedBlackTree<int,int>::iterator beg = a.begin();
	//std::map<int,int>::iterator end = a.end();

	a.swap(b);

	while (beg != b.end())
		beg++;

	std::cout << "end" << '\n';
	return (0);
}
