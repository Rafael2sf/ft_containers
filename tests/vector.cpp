#include "../includes/vector.hpp"
#include <iomanip>

#define SIZE 10000000
#define TYPE int

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
void	__tester_function(std::string info,  T const & v1, T const & v2 )
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

template< class T>
void	__tester_manual_compare(ft::vector<T> const & v1, std::vector<T> const & v2)
{
	std::cout << std::setw(15) <<  "% compare %" << "\t| ";
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
}

int	main( void )
{
	ft::vector<TYPE>	v1;
	std::vector<TYPE>	v2;

	std::cout << std::setw(15) << "\t";
	std::cout << std::setw(20) << "[ft::vector]";
	std::cout << "\t";
	std::cout << std::setw(20) << "[std::vector]";
	std::cout << std::endl << std::endl;

	__tester_function<size_t>("max_size", v1.max_size(), v2.max_size());
	__tester_function<size_t>("size", v1.size(), v2.size());
	__tester_function<size_t>("capacity", v1.capacity(), v2.capacity());

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

	__tester_manual_compare<TYPE>(v1, v2);
	__tester_function<size_t>("size", v1.size(), v2.size());
	__tester_function<size_t>("capacity", v1.capacity(), v2.capacity());

	// pop_back

	std::cout << std::setw(15) << "pop_back" << "\t|\t    ";
	for (int i = 0; i < SIZE / 2; i++)
	{
		if (i % (SIZE / 20) == 0)
		{
			std::cout << "-";
			std::cout.flush();
		}
		v1.pop_back();
	}
	std::cout << "\t\t  ";
	for (int i = 0; i < SIZE / 2; i++)
	{
		if (i % (SIZE / 20) == 0)
		{
			std::cout << "-";
			std::cout.flush();
		}
		v2.pop_back();
	}
	std::cout << " [OK]" << std::endl;

	__tester_manual_compare<TYPE>(v1, v2);
	__tester_function<size_t>("size", v1.size(), v2.size());
	__tester_function<size_t>("capacity", v1.capacity(), v2.capacity());

	try { std::cout << "\t" << v1.at(SIZE); } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }
	try { std::cout << "\t" << v2.at(SIZE); } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }

	v1.clear();
	v2.clear();
	return (0);
}
