#include <iostream>
#include <iomanip>

#include "../includes/type_traits.hpp"
//#include <type_traits>

template <class T, class U = void>
struct Foo {
	static const int value = 0;
};

template <class T>
struct Foo<T, typename ft::enable_if<ft::is_integral<T>::value>::type> {
	static const int value = 1;
};

int	main( void )
{
	std::cout << Foo<int>::value << std::endl;
	return (0);
}
