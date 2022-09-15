#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../includes/map.hpp"
#include "../includes/vector.hpp"
#include "../includes/utility.hpp"

#define PRINT(X) { std::cout << X << std::endl; }
#define INFO(X) { map_info(X); }
#define ITER(X) { map_iter(X); }
#define LOG(X) { map_info(X); map_iter(X); }
#define OBJ ft::map

template<class T>
void	map_info( T & x )
{
	if (x.empty())
		std::cout << "[ empty ]";
	else
	{
		std::cout << "[ (" << (x.begin())->first << "," << (x.begin())->second << ") ";
		std::cout << " ... ";
		std::cout << '(' << (--x.end())->first << "," << (--x.end())->second << ") ]";
	}
	std::cout<< " size: " << x.size() << std::endl;
}

template<class T>
void	map_iter( T const& x )
{
	typename T::const_iterator it = x.begin();

	if (x.empty())
		return ;
	std::cout << "{ ";
	while(it != x.end())
	{
		std::cout << '(' << (it)->first << ", " << (it)->second << ") ";
		it++;
	}
	std::cout << "}" << std::endl;
}

int	main( void )
{
	/* for range testing */
	ft::vector< ft::pair<int, std::string> > v;
		for (int i = 0; i < 10; i++)
			v.push_back(ft::make_pair(i, "^-^"));

	{
		PRINT("%% TEST 0 :: Constructors %%");

		typedef OBJ<int, std::string> Local;
		Local	m0;
		LOG(m0);
		Local	m1(v.begin(), v.end());
		LOG(m1);
		Local	m2(m1);
		m1.clear();
		LOG(m1);
		LOG(m2);
		m0 = m2;
		m2.clear();
		LOG(m0);
		LOG(m2);
		m2.swap(m0);
		LOG(m0);
		LOG(m2);
	}
	{
		PRINT("%% TEST 1 :: Inserting %%");

		typedef OBJ<int, std::string> Local;
		ft::pair<Local::iterator, bool> ret;
		Local::iterator	it;
		Local	m0;
		for (int i = 0; i < 10; i++)
		{
			ret = m0.insert(ft::make_pair(42 - i, "UwU"));
			std::cout << ret.first->first << " " << ret.first->second;
			std::cout << " " << std::boolalpha << ret.second << std::endl;
			ret = m0.insert(ft::make_pair(42 - i, "UwU"));
			std::cout << ret.first->first << " " << ret.first->second;
			std::cout << " " << std::boolalpha << ret.second << std::endl;
			std::cout << std::endl;
		}
		LOG(m0);
		it = m0.insert(m0.end(), ft::make_pair(0, "begin"));
		std::cout << it->first << " " << it->second << '\n';
		it = m0.insert(m0.begin(), ft::make_pair(50, "end"));
		std::cout << it->first << " " << it->second << '\n';
		it = m0.insert(m0.begin(), ft::make_pair(50, "end"));
		std::cout << it->first << " " << it->second << '\n';
		LOG(m0);
		m0.insert(v.begin(), v.end());
		LOG(m0);
		m0[420] = "Hello World";
		m0[690] = "Not so fast!";
		LOG(m0);

		PRINT("%% TEST 2 :: acess %%");

		PRINT(m0[3]);
		PRINT(m0[33]);
		PRINT(m0[50]);
		PRINT(m0.at(3));
		PRINT(m0.at(33));
		PRINT(m0.at(50));
		try
		{ PRINT(m0.at(39210931)); }
		catch (std::exception & e )
		{ PRINT(e.what()); }

		PRINT("%% TEST 3 :: operations %%");

		it = m0.lower_bound(-1);
		if (it != m0.end())
			PRINT(it->first << " " << it->second);
		if (it == m0.end())
			PRINT("END");

		it = m0.lower_bound(1000);
		if (it != m0.end())
			PRINT(it->first << " " << it->second);
		if (it == m0.end())
			PRINT("END");


		it = m0.lower_bound(33);
		if (it != m0.end())
			PRINT(it->first << " " << it->second);
		if (it == m0.end())
			PRINT("END");

		it = m0.lower_bound(50);
		if (it != m0.end())
			PRINT(it->first << " " << it->second);
		if (it == m0.end())
			PRINT("END");

		// it = m0.upper_bound(-1);
		// if (it != m0.end())
		// 	PRINT(it->first << " " << it->second);
		// it = m0.upper_bound(1000);
		// if (it != m0.end())
		// 	PRINT(it->first << " " << it->second);
		// it = m0.upper_bound(33);
		// if (it != m0.end())
		// 	PRINT(it->first << " " << it->second);
		// it = m0.upper_bound(50);
		// if (it != m0.end())
		// 	PRINT(it->first << " " << it->second);

		PRINT("%% TEST 4 :: erasing %%");

		it = m0.begin();
		it++; it++; it++;
		m0.erase(m0.begin(), it);
		LOG(m0);
		it = m0.end();
		it--; it--; it--;
		m0.erase(it, m0.end());
		LOG(m0);
		PRINT(m0.erase(3));
		PRINT(m0.erase(0));
		PRINT(m0.erase(33));
		PRINT(m0.erase(50));
		PRINT(m0.erase(100));
		LOG(m0);
		m0.erase(--m0.end());
		while (m0.begin() != m0.end())
			m0.erase(m0.begin());
		LOG(m0);
	}
	return (0);
}
