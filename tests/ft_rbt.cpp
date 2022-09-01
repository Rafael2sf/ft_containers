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

	// ft::vector< ft::pair<int, int> >v;
	// for (int i = 0; i < 1000000; i++)
	// 	v.push_back(ft::make_pair<int, int>(rand() % 1000000, i));

	ft::RedBlackTree<int, int>				t;

	for (int i = 0; i < 42; i++)
		t.insert(ft::make_pair<int, int>(i, 100 + i));
	// std::cout << m.size() << '\n';
	// for (int i = 0; i < 10000000; i++)
	// 	m.erase(42);

	t.print();
	ft::RedBlackTree<int, int>::iterator it2;
	ft::RedBlackTree<int, int>::iterator it = t.begin();
	for (; it != t.end(); ++it)
		std::cout << (*it).data->first << " " << (*it).data->second << std::endl;
	std::cout << (*it).data->first << " " << (*it).data->second << std::endl;

	// std::cout << (*(++it)).data->second << std::endl;
	// std::cout << (*(++it)).data->second << std::endl;
	// std::cout << (*(++it)).data->second << std::endl;
	// std::cout << (*(++it)).data->second << std::endl;
	//std::cout << (*(++it)).data->second << std::endl;
	// std::cout << (*(--it)).data->second << std::endl;
	// std::cout << (*(--it)).data->second << std::endl;
	// std::cout << (*(--it)).data->second << std::endl;
	// std::cout << (*(--it)).data->second << std::endl;
	// std::cout << (*(--it)).data->second << std::endl;
	// std::cout << (*(--it)).data->second << std::endl;
	//bar.print();
	return (0);
}
