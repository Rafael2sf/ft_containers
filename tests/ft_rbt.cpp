#include <stdlib.h>
#include <map>
#include "../includes/RedBlackTree.hpp"

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

int main( void )
{
	ft::RedBlackTree<int, int> tree;
	//srand(time(NULL));
	for (int i = 0; i < 1000000; i++)
		tree.insert(ft::pair<int, int>(i, i));
	for (int i = 0; i < 500000; i++)
		tree.erase((rand() % 1000000) - 1);
	// tree.insert(ft::pair<int, int>(10, 42));
	// tree.insert(ft::pair<int, int>(5, 42));
	// tree.insert(ft::pair<int, int>(30, 42));
	// tree.insert(ft::pair<int, int>(1, 42));
	// tree.insert(ft::pair<int, int>(7, 42));
	// tree.insert(ft::pair<int, int>(25, 42));
	// tree.insert(ft::pair<int, int>(40, 42));
	// tree.insert(ft::pair<int, int>(20, 42));
	// tree.insert(ft::pair<int, int>(28, 42));
	// std::cout << "last element" << '\n';
	// tree.insert(ft::pair<int, int>(80, 42));
	// tree.print();
	// tree.erase(0);
	// tree.all_black();
	// tree.nodeFind(25)->color = ft::red;
	// // tree.print();
	// tree.erase(1);
	// tree.print();
	std::cout << (tree.isValid() ? "true" : "false") << std::endl;
	std::cout << (tree.inOrder() ? "true" : "false") << std::endl;
	return (0);
}
