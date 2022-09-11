#include <map>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <iterator>
#include "../includes/RedBlackTree.hpp"
#include "../includes/vector.hpp"
#include "../includes/type_traits.hpp"

class Foo
{
	public:
		~Foo() {}
		Foo( void ): _bar(0) {}
		Foo( int n ): _bar(n) {}
		Foo( Foo const& r) {*this = r;}
		Foo & operator=(Foo const& other) {_bar = other._bar; return *this;}
		bool	operator<(Foo const& other) const {
			return (_bar < other._bar);
		}
	private:
		int _bar;
};

template <class T>
struct MyAlloc
{
	typedef typename std::allocator<T>::pointer		pointer;
	typedef typename std::allocator<T>::size_type	size_type;

	pointer
	allocate( size_type _n, void const* hint = 0 )
	{
		std::cout << "custom allocate" << "\n";
		return std::allocator<T>::allocate(_n);
	}

	pointer
	deallocate( size_type _n, void const* hint = 0 )
	{
		std::cout << "custom deallocate" << "\n";
		return std::allocator<T>::allocate(_n);
	}
};

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
	{
		ft::RedBlackTree<int, int> t;
		t[1] = 42;
		t[2] = 42;
		t[3] = 42;
		std::cout << t[1] << '\n';
		iter_print(t.begin(), t.end());
	}
	return (0);
}
