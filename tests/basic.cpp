#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
// #include <type_traits>

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
	std::vector<int>	x;
	x.push_back(1);
	x.push_back(2);

	std::vector<int>::iterator	it1 = x.begin() + 1;
	std::vector<int>::iterator	it2 = it1;
	(void)it2;
	std::cout << *it1 << std::endl;
	std::cout << *it1.base() << std::endl;

	//int	arr[] = {1, 2, 3};

	// for (size_t i = 0; i < 10; i++)
	// 	b.push_back(i);
	// for (size_t i = 0; i < 16; i++)
	// 	a.push_back(i);

	//a.assign(b.begin(), b.end());
	// a.assign(a.begin(), a.end());

	// ft::vector<int>	b(a.begin(), a.end());

	// // std::vector<int>::iterator r = a.erase(a.end(), a.begin());
	// // if (r == a.end())
	// // 	std::cout << "end" << std::endl;
	// // else
	// // 	std::cout << "r: " << *r << std::endl;

	// for (std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
	// 	std::cout << "~ " << *it << std::endl;

	// std::cout << std::endl;
	// std::cout << "size: " << a.size() << std::endl;
	// std::cout << "capacity: " << a.capacity() << std::endl;
	return (0);
}
