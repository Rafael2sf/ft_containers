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
	srand(time(NULL));
	for (int i = 0; i < 10000000; i++)
		tree.insert(ft::pair<int, int>(i, i));
	for (int i = 0; i < 10000000; i++)
		tree.erase(rand() % (10000000 - 1));
	std::cout << (tree.isValid() ? "true" : "false") << std::endl;
	std::cout << (tree.inOrder() ? "true" : "false") << std::endl;
	return (0);
}
