#include "vector.hpp"
#include <iomanip>

class Foo
{
	public:
		~Foo() { }
		Foo( void ): foo(0) { }
		Foo( int val ): foo(val) { }
		Foo( Foo const & ref ) { *this = ref; }
		Foo & operator=( Foo const & ref) { this->foo = ref.foo; return (*this); }
		void	print( void ) const { std::cout << this->foo << std::endl; }
		int	foo;
};

template< typename T>
void	tester(std::string info,  T const & v1, T const & v2 )
{
	std::cout << std::setw(15) << info << "\t| ";
	std::cout << std::setw(20) << v1;
	std::cout << "\t";
	std::cout << std::setw(20) << v2;
	if (v1 == v2)
		std::cout << " [OK]";
	else
		std::cout << " [KO]";
	std::cout << std::endl;
}

#define SIZE 10000000

int	main( void )
{
	ft::vector<int>		v1;
	std::vector<int>	v2;

	std::cout << std::setw(15) << "\t";
	std::cout << std::setw(20) << "[ft::vector]";
	std::cout << "\t";
	std::cout << std::setw(20) << "[std::vector]";
	std::cout << std::endl << std::endl;

	// push_back
	std::cout << std::setw(15) << "push_back" << "\t|\t    ";
	for (int i = 0; i < SIZE; i++)
	{
		if (i % (SIZE / 10) == 0)
		{
			std::cout << "-";
			std::cout.flush();
		}
		v1.push_back(i);
	}
	std::cout << "\t\t  ";
	for (int i = 0; i < SIZE; i++)
	{
		if (i % (SIZE / 10) == 0)
		{
			std::cout << "-";
			std::cout.flush();
		}
		v2.push_back(i);
	}
	std::cout << " [OK]" << std::endl;

	tester<size_t>("size", v1.size(), v2.size());
	tester<size_t>("max_size", v1.max_size(), v2.max_size());
	tester<size_t>("capacity", v1.capacity(), v2.capacity());

	std::cout << std::setw(15) <<  "==" << "\t| ";
	for (int i = 0; i < SIZE; i++)
	{
		if (v1[i] != v2[i])
		{
			std::cout << "\t\t\t\t\t     [KO]" << std::endl;
			break ;
		}
		else if ( i == SIZE - 1)
		{
			std::cout << "\t\t\t\t\t     [OK]" << std::endl;
		}
	}
	
	v1.clear();
	v2.clear();
	return (0);
}
