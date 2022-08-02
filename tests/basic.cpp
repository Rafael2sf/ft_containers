#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>

#include "../includes/vector.hpp"
#include "../includes/iterators.hpp"

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

int	main( void )
{
	ft::vector<float> a;

	for (int i = 0; i < 10; i++)
		a.push_back(i);

	ft::vector<float>::iterator it1 = a.begin();
	ft::vector<float>::iterator it2 = 1 + it1;

	// ft::vector<float> b(10, 10);
	// for (size_t i = 0; i < a.size(); i++)
	// 	std::cout << a.at(i) << std::endl;

	//numbers.reserve(100);
	// for (int i = 0; i < 100; i++)
	// 	numbers.push_back(i);
	// for (int i = 0; i < 100; i++)
	// 	std::cout << i << ": " << numbers[i] << std::endl;
	// ft::vector<int, myAlloc<int> >::iterator	it1 = numbers.begin();
	// ft::vector<int, myAlloc<int> >::iterator	it2 = numbers.end();

	// std::cout << *it1 << " " << *it2 << std::endl;
	// it1++;
	// it2--;
	// std::cout << *it1 << " " << *it2 << std::endl;
	// it1 += 3;
	// it2 -= 3;
	// std::cout << *it1 << " " << *it2 << std::endl;
	// std::cout << (it2 == it1 ? "true" : "false") << std::endl;
	// std::cout << (it2 != it1 ? "true" : "false") << std::endl;
	// std::cout << (it2 < it1 ? "true" : "false") << std::endl;
	// std::cout << (it2 > it1 ? "true" : "false") << std::endl;
	// std::cout << (it2 <= it1 ? "true" : "false") << std::endl;
	// std::cout << (it2 >= it1 ? "true" : "false") << std::endl;
	// it2 = it1;
	// std::cout << (it2 == it1 ? "true" : "false") << std::endl;
	return (0);
}
