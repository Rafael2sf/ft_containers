#include <map>
#include <vector>
#include <utility>
#include <stdlib.h>
#include "../includes/RedBlackTree.hpp"
#include "../includes/vector.hpp"

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
		std::cout << "hi\n";
		return std::allocator<T>::allocate(_n);
	}

	pointer
	deallocate( size_type _n, void const* hint = 0 )
	{
		std::cout << "hi\n";
		return std::allocator<T>::allocate(_n);
	}
};

int main( void )
{
	//typedef typename x::template rebind<std::string>::other _alloc_type;
	// srand(time(NULL));

	// ft::RedBlackTree<int, int>	t1;
	// for (int i = 0; i < 16; i++)
	// 	t1.insert(ft::make_pair<int, int>(i, 100 + i));

	// t1.print();
	// std::cout << (t1.begin() == t1.end()) << '\n';

	// ft::RedBlackTree<int, int>	t2(t1.begin(), t1.end()); //(t1.begin(), t1.end());

	// std::cout << t2.size() << '\n';
	// std::cout << t1.size() << '\n';

	ft::RbtNode<ft::pair<int, int> > * n = new ft::RbtNode<ft::pair<int, int> >(1);

	ft::RbtIterator< ft::pair<int, int>*> x(n);
	ft::RbtIterator< const ft::pair<int, int> *> y(n);

	x->first = 10;
	y->first = 10;

	//ft::RbtIterator< int* > y()
	//ft::RbtIterator< const int* > y = ft::RbtIterator(&i)

	// ft::RedBlackTree<int, int>::iterator it = t2.begin();
	// //(*it) = ft::pair<int, int>(0, 0);
	// while (it != t2.end())
	// {
	// 	std::cout << (*it).first << " " << (*it).second << std::endl;
	// 	it++;
	// }
	// it++;
	// std::cout << (*it).first << " " << (*it).second << std::endl;
}
