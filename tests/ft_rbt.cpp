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
	srand(time(NULL));

	ft::vector< ft::pair<int, int> >v;
	for (int i = 0; i < 1000000; i++)
		v.push_back(ft::make_pair<int, int>(rand() % 1000000, i));

	ft::RedBlackTree<int, int>		m(v.begin(), v.end());
	std::cout << m.size() << std::endl;

	// for (int i = 0; i < 10000000; i++)
	// 	m.insert(ft::make_pair<int, int>(42, 42));
	// std::cout << m.size() << '\n';
	// for (int i = 0; i < 10000000; i++)
	// 	m.erase(42);

	//m.print();

	// it = m.begin();
	// std::cout << (*it).data->second << std::endl;
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
