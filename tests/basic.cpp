#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>

#include "../includes/vector.hpp"
#include "../includes/iterators.hpp"

int	main( void )
{
	ft::vector<int>	numbers;

	numbers.reserve(100);
	for (int i = 0; i < 100; i++)
		numbers.push_back(i);
	// for (int i = 0; i < 100; i++)
	// 	std::cout << i << ": " << numbers[i] << std::endl;
	for (ft::vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
		std::cout << *it << std::endl;
	return (0);
}
