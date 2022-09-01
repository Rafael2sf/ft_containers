#include <map>
#include <vector>
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

int main( void )
{
	// srand(time(NULL));

	ft::RedBlackTree<int, int>	t;
	for (int i = 0; i < 100; i++)
		t.insert(ft::make_pair<int, int>(i, 100 + i));

	ft::RedBlackTree<int, int>::iterator it = t.begin();
	while (it != t.end())
	{
		std::cout << (*it).data->first << " " << (*it).data->second << std::endl;
		it++;
	}
	it++;
	std::cout << (*it).data->first << " " << (*it).data->second << std::endl;
	return (0);
}
