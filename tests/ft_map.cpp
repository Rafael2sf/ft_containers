#include <iostream>
#include <string>
#include "map.hpp"
#include "vector.hpp"

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
		typedef OBJ< int, std::string, std::greater<int> > Local;
		PRINT("%%> 0 :: Constructors <%%");

		Local	m0;
		LOG(m0);
		Local	m1(v.begin(), v.end());
		LOG(m1);
		Local	m2(m1);
		m1.clear();
		LOG(m1);
		LOG(m2);
		m0 = m0;
		LOG(m0);
		m0 = m2;
		m2.clear();
		LOG(m0);
		LOG(m2);
		m2.swap(m0);
		LOG(m0);
		LOG(m2);

		m0.key_comp();
		m0.value_comp();
		m0.get_allocator();
	}
	{
		typedef OBJ<int, std::string> Local;
		PRINT("%%> 1 :: Inserting <%%");

		ft::pair<Local::iterator, bool> ret;
		Local::iterator	it;
		Local	m0;
		for (int i = 0; i < 10; i++)
		{
			ret = m0.insert(ft::make_pair(42 - i, "UwU"));
			PRINT(ret.first->first << " " << ret.first->second);
			PRINT(" " << std::boolalpha << ret.second << std::endl);
			ret = m0.insert(ft::make_pair(42 - i, "UwU"));
			PRINT(ret.first->first << " " << ret.first->second);
			PRINT(" " << std::boolalpha << ret.second);
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

		PRINT("%%> 2 :: acess <%%");

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

		PRINT("%%> 3 :: operations <%%");

		PRINT(m0.value_comp()(*it, *++it));

		it = m0.lower_bound(-1); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.lower_bound(0); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.lower_bound(33); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.lower_bound(49); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.lower_bound(50); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.lower_bound(51); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.lower_bound(420); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.lower_bound(1000); if (it != m0.end()) PRINT(it->first << " " << it->second);

		it = m0.upper_bound(-1); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.upper_bound(0); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.upper_bound(33); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.upper_bound(49); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.upper_bound(50); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.upper_bound(51); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.upper_bound(420); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.upper_bound(1000); if (it != m0.end()) PRINT(it->first << " " << it->second);

		std::cout << "here" << std::endl;

		PRINT(m0.count(-1));
		PRINT(m0.count(0));
		PRINT(m0.count(33));
		PRINT(m0.count(420));
		PRINT(m0.count(100));

		it = m0.find(-1); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.find(0); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.find(33); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.find(42); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.find(50); if (it != m0.end()) PRINT(it->first << " " << it->second);
		it = m0.find(421); if (it != m0.end()) PRINT(it->first << " " << it->second);

		/* lower_bound and upper_bound are correct therefore so is equal_range */

		PRINT("%%> 4 :: iterators <%%");

		Local::const_iterator	cit;
		Local::reverse_iterator	rit;
		Local::const_reverse_iterator	rcit;

		for (it = m0.begin(); it != m0.end(); it++)
			PRINT(it->first << " " << it->second);
		for (cit = m0.begin(); cit != m0.end(); cit++)
			PRINT(cit->first << " " << cit->second);
		for (rit = m0.rbegin(); rit != m0.rend(); rit++)
			PRINT(rit->first << " " << rit->second);
		for (rcit = m0.rbegin(); rcit != m0.rend(); rcit++)
			PRINT(rcit->first << " " << rcit->second);

		it = --m0.begin();
		if (it == m0.end())
			PRINT("iter = END")
		it = m0.end();
		++it;
		if (it != m0.end())
		{
			PRINT((*it).first << " " << (*it).second);
			it->second = "this mapped_type has been overwritten";
		}

		rcit = rit;
		cit = it;
		(void)(it == cit);
		(void)(cit == it);
		(void)(it != cit);
		(void)(cit != it);
		(void)(rit == rcit);
		(void)(rcit == rit);
		(void)(rit != rcit);
		(void)(rcit != rit);

		for (it = --m0.end(); it != m0.begin(); it--)
			PRINT(it->first << " " << it->second);
		for (cit = --m0.end(); cit != m0.begin(); cit--)
			PRINT(cit->first << " " << cit->second);
		for (rit = --m0.rend(); rit != m0.rbegin(); rit--)
			PRINT(rit->first << " " << rit->second);
		for (rcit = --m0.rend(); rcit != m0.rbegin(); rcit--)
			PRINT(rcit->first << " " << rcit->second);

		PRINT("%%> 5 :: erasing <%%");

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
		m0.erase(--m0.end());
		LOG(m0);
		it = m0.begin();
		m0.erase(++m0.begin());
		m0.erase(++m0.begin());
		m0.erase(++m0.begin());
		for ( ; it != m0.end(); it++)
			PRINT(it->first << " " << it->second);
		while (m0.begin() != m0.end())
			m0.erase(m0.begin());
		LOG(m0);
	}
	{
		typedef const OBJ<int, float> Local;
		PRINT("%%> 6 :: const <%%");

		Local m0;
		m0.begin();
		m0.end();
		m0.rbegin();
		m0.rend();
		m0.empty();
		m0.size();
		m0.max_size();
		try
		{ PRINT(m0.at(42)); }
		catch (std::exception & e )
		{ PRINT(e.what()); }
		m0.key_comp();
		m0.value_comp();
		m0.find(42);
		m0.count(42);
		m0.lower_bound(42);
		m0.upper_bound(42);
		m0.equal_range(42);
		m0.get_allocator();
	}
	{
		typedef OBJ<char, int> Local;
		PRINT("%%> 7 :: non-member <%%");

		Local m0, m1;

		PRINT(std::boolalpha << (m0 == m1));
		PRINT(std::boolalpha << (m0 != m1));
		PRINT(std::boolalpha << (m0 < m1));
		PRINT(std::boolalpha << (m0 > m1));
		PRINT(std::boolalpha << (m0 <= m1));
		PRINT(std::boolalpha << (m0 >= m1));

		m0.insert(ft::make_pair('a', 0));
		PRINT("");
		m1.insert(ft::make_pair('b', 0));

		PRINT(std::boolalpha << (m0 == m1));
		PRINT(std::boolalpha << (m0 != m1));
		PRINT(std::boolalpha << (m0 < m1));
		PRINT(std::boolalpha << (m0 > m1));
		PRINT(std::boolalpha << (m0 <= m1));
		PRINT(std::boolalpha << (m0 >= m1));

		LOG(m0);
		swap(m0, m1);
		LOG(m0);
	}
	{
		typedef OBJ<int, int> Local;
		PRINT("%%> 8 :: performance <%%");

		Local	m0;
		Local	v1;
		Local::iterator	it;
		const size_t size = 1000000;

		for (size_t i = 0; i < size; i++)
			m0.insert(ft::make_pair(i, 42));
		v1.insert(m0.begin(), m0.end());
		for (size_t i = 0; i < size; i++)
			m0.lower_bound(m0.find(i)->first);
		for (size_t i = 0; i < size; i++)
			m0.erase(m0.begin());
		v1.erase(v1.begin(), v1.end());
	}
	return (0);
}
