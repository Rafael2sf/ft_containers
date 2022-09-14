#include <iostream>
#include "../includes/map.hpp"
#include <map>

template<class T, class U>
void	TEST_INFO( ft::map<T, U> const& v )
{
	if (v.empty())
	{
		std::cout << var << " = [ ]";
	}
	else
	{
		std::cout << "[ (" << v.begin()->first << "," << v.begin()->second << ") ";
		std::cout << " ... ";
		std::cout << '(' << v.end()->first << "," << v.end()->second << ") ]";
	}
	std::cout<< " size: " << v.size();
	std::cout << std::endl;
}

template<class T, class U>
void	TEST_PRINT( ft::map<T, U> & v )
{
	typename ft::map<T, U>::iterator it = v.begin();

	std::cout << "{ ";
	while(it != v.end())
		std::cout << '(' << (it++)->first << "," << (it++)->second << ") ";
	std::cout << "}" << std::endl;
}

int	main( void )
{
	ft::map<int, int>	t;

	TEST_INFO(t);
	TEST_PRINT(t);

	return (0);
}
