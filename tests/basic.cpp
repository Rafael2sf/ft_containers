#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
// #include <type_traits>

#include "../includes/vector.hpp"
#include "../includes/iterators.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/utility.hpp"

template <typename T>
class	myAlloc: public std::allocator<T>
{
	public:
		T * allocate(size_t n, const void *idk = 0)
		{
			std::cout << "Allocated " << n << "*T bytes" << std::endl;
			return std::allocator<T>::allocate(n, idk);
		}
};

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
	std::vector<int> a;
	std::vector<int> b;

	b.push_back(100);
	a.push_back(1);
	a.push_back(2);

	std::cout << (b > a) << std::endl;
	return (0);
}
