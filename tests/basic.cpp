#include <iostream>
// #include <iomanip>
// #include <vector>
// #include <utility>

#include "../includes/vector.hpp"
#include "../includes/iterators.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/utility.hpp"

// template <typename T>
// class	myAlloc: public std::allocator<T>
// {
// 	public:
// 		T * allocate(size_t n, const void *idk = 0)
// 		{
// 			std::cout << "Allocated " << n << "*T bytes" << std::endl;
// 			return std::allocator<T>::allocate(n, idk);
// 		}
// };

// template <class T>
// void	it_loop(typename ft::vector<T>::iterator it, typename ft::vector<T>::iterator ite)
// {
// 	std::cout << "[ ";
// 	while (it != ite)
// 		std::cout << *it++ << " ";
// 	std::cout << "]" << std::endl;
// }

int	main( void )
{
	//ft::vector<int>	a;
	ft::vector<int>	b;

	for (size_t i = 1; i < 16; i++)
		b.push_back(i);
	// for (size_t i = 0; i < 3; i++)
	// 	a.push_back(i);

	//a.push_back(9);
	//a.insert(a.begin(), b.begin(), b.end());

	for (ft::vector<int>::iterator it = b.begin(); it != b.end(); it++)
		std::cout << "~ " << *it << std::endl;

	std::cout << std::endl;
	std::cout << "size: " << b.size() << std::endl;
	std::cout << "capacity: " << b.capacity() << std::endl;
	//std::cout << *ret << std::endl;

	// if (ft::is_integral<int>())
	// 	std::cout << "OK" << std::endl;
	return (0);
}
