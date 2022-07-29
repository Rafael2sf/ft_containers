#include "../includes/vector.hpp"

int	main( void )
{
	std::vector<int>	a;

	a.reserve(10);
	std::cout << a.capacity() << std::endl;
	for (int i = 0; i < 10; i++)
		a.push_back(i);
	a.resize(0);
	// for (int i = 0; i < 5; i++)
	// 	std::cout << a.at(i) << std::endl;
	std::cout << a.capacity() << " " << a.size() << std::endl;
	return (0);
}
