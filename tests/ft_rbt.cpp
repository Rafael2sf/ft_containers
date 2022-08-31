#include <map>
#include <vector>
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
	// std::map<int, int>				m;
	// std::map<int, int>::iterator	it = m.begin();
	ft::RedBlackTree<int, int>				m;
	ft::RedBlackTree<int, int>::iterator	it;

	m[10] = 5;
	m[6] = 3;
	m[15] = 6;
	m[4] = 1;
	m[7] = 4;
	m[5] = 2;

	// it = m.begin();
	// std::cout << (*it).data->second << std::endl;
	// std::cout << (*(++it)).data->second << std::endl;
	// std::cout << (*(++it)).data->second << std::endl;
	// std::cout << (*(++it)).data->second << std::endl;
	// std::cout << (*(++it)).data->second << std::endl;
	// //std::cout << (*(++it)).data->second << std::endl;

	// std::cout << (*(--it)).data->second << std::endl;
	// std::cout << (*(--it)).data->second << std::endl;
	// std::cout << (*(--it)).data->second << std::endl;
	// std::cout << (*(--it)).data->second << std::endl;
	// std::cout << (*(--it)).data->second << std::endl;
	// std::cout << (*(--it)).data->second << std::endl;

	return (0);
}
