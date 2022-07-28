#include "vector.hpp"
#include <iomanip>

template< typename T>
void	tester( T const & v1, T const & v2)
{
	std::cout << std::setw(20) << v1;
	std::cout << "\t";
	std::cout << std::setw(20) << v2 << std::endl;
}

int	main( void )
{
	ft::vector<int>		v1;
	std::vector<int>	v2;

	std::allocator<int> a;

	tester<size_t>(v1.max_size(), v2.max_size());
	tester<size_t>(v1.size(), v2.size());

	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	std::cout << v2[0] <<std::endl;
	// std::cout << v2[1] <<std::endl;
	// std::cout << v2[2] <<std::endl;

	return (0);
}
