#include <iostream>
#include "map.hpp"
#include <map>

int	main( void )
{
	ft::map<int, int> x;
	ft::map<int, int>::iterator ibeg;
	ft::map<int, int>::iterator iera;
	ft::map<int, int>::iterator iend;

	for (int i = 10; i < 18; i++)
		x.insert(ft::make_pair(i, i));

	ibeg = x.begin();
	iera = x.find(13);
	iend = x.end();
	//x.erase(x.find(100));
	x.erase(iera);
	//std::cout << "new begin: " << x.begin()->first << std::endl;
	//x.erase(++x.begin());
	//std::cout << ft::map<int, int>::iterator(x.begin()._M_node->parent)->first  << std::endl;
	//std::cout << ibeg._M_node << " " << x.begin()._M_node << std::endl;

	while (ibeg != iend)
		std::cout << ibeg++->first << std::endl;
	return (0);
}
