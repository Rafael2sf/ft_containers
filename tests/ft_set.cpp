#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "../includes/set.hpp"
#include "../includes/vector.hpp"

#define PRINT(X) { std::cout << X << std::endl; }
#define INFO(X) { set_info(X); }
#define ITER(X) { set_iter(X); }
#define LOG(X) { set_info(X); set_iter(X); }
#define OBJ ft::set

template<class T>
void	set_info( T & x )
{
	if (x.empty())
		std::cout << "[ empty ]";
	else
	{
		std::cout << "[ (" << *x.begin() << ") ";
		std::cout << " ... ";
		std::cout << '(' << *--x.end() << ") ]";
	}
	std::cout<< " size: " << x.size() << std::endl;
}

template<class T>
void	set_iter( T const& x )
{
	typename T::const_iterator it = x.begin();

	if (x.empty())
		return ;
	std::cout << "{ ";
	while(it != x.end())
	{
		std::cout << '(' <<  *it << ") ";
		it++;
	}
	std::cout << "}" << std::endl;
}

int	main( void )
{
	/* for range testing */
	ft::vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	{
		typedef OBJ<int, std::greater<int> > Local;
		PRINT("%%> 0 :: Constructors <%%");

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

		m0.key_comp();
		m0.value_comp();
		m0.get_allocator();
	}
	{
		typedef OBJ<int> Local;
		PRINT("%%> 1 :: Inserting <%%");

		ft::pair<Local::iterator, bool> ret;
		Local::iterator	it;
		Local	m0;
		for (int i = 0; i < 10; i++)
		{
			ret = m0.insert(i);
			PRINT(*ret.first);
			PRINT(" " << std::boolalpha << ret.second << std::endl);
			ret = m0.insert(100);
			PRINT(*ret.first);
			PRINT(" " << std::boolalpha << ret.second);
		}
		LOG(m0);
		it = m0.insert(m0.end(), -1);
		PRINT(*it);
		it = m0.insert(m0.begin(), 100);
		PRINT(*it);
		it = m0.insert(m0.begin(), 1000);
		PRINT(*it);
		LOG(m0);
		m0.insert(v.begin(), v.end());
		LOG(m0);

		PRINT("%%> 2 :: operations <%%");

		PRINT(m0.value_comp()(*it, *++it));

		it = m0.lower_bound(-1); if (it != m0.end()) PRINT(*it);
		it = m0.lower_bound(0); if (it != m0.end()) PRINT(*it);
		it = m0.lower_bound(33); if (it != m0.end()) PRINT(*it);
		it = m0.lower_bound(49); if (it != m0.end()) PRINT(*it);
		it = m0.lower_bound(50); if (it != m0.end()) PRINT(*it);
		it = m0.lower_bound(51); if (it != m0.end()) PRINT(*it);
		it = m0.lower_bound(420); if (it != m0.end()) PRINT(*it);
		it = m0.lower_bound(1000); if (it != m0.end()) PRINT(*it);

		it = m0.upper_bound(-1); if (it != m0.end()) PRINT(*it);
		it = m0.upper_bound(0); if (it != m0.end()) PRINT(*it);
		it = m0.upper_bound(33); if (it != m0.end()) PRINT(*it);
		it = m0.upper_bound(49); if (it != m0.end()) PRINT(*it);
		it = m0.upper_bound(50); if (it != m0.end()) PRINT(*it);
		it = m0.upper_bound(51); if (it != m0.end()) PRINT(*it);
		it = m0.upper_bound(420); if (it != m0.end()) PRINT(*it);
		it = m0.upper_bound(1000); if (it != m0.end()) PRINT(*it);

		PRINT(m0.count(-1));
		PRINT(m0.count(0));
		PRINT(m0.count(33));
		PRINT(m0.count(420));
		PRINT(m0.count(100));

		it = m0.find(-1); if (it != m0.end()) PRINT(*it);
		it = m0.find(0); if (it != m0.end()) PRINT(*it);
		it = m0.find(33); if (it != m0.end()) PRINT(*it);
		it = m0.find(42); if (it != m0.end()) PRINT(*it);
		it = m0.find(50); if (it != m0.end()) PRINT(*it);
		it = m0.find(421); if (it != m0.end()) PRINT(*it);

		/* lower_bound and upper_bound are correct therefore so is equal_range */

		PRINT("%%> 3 :: iterators <%%");

		for (Local::iterator iter = m0.begin(); iter != m0.end(); iter++)
			PRINT(*iter);
		for (Local::const_iterator iter = m0.begin(); iter != m0.end(); iter++)
			PRINT(*iter);
		for (Local::reverse_iterator iter = m0.rbegin(); iter != m0.rend(); iter++)
			PRINT(*iter);
		for (Local::const_reverse_iterator iter = m0.rbegin(); iter != m0.rend(); iter++)
			PRINT(*iter);

		it = --m0.begin();
		if (it == m0.end())
			PRINT("iter = END")
		it = m0.end();
		++it;
		if (it != m0.end())
			PRINT(*it);

		for (Local::iterator iter = --m0.end(); iter != m0.begin(); iter--)
			PRINT(*iter);
		for (Local::const_iterator iter = --m0.end(); iter != m0.begin(); iter--)
			PRINT(*iter);
		for (Local::reverse_iterator iter = --m0.rend(); iter != m0.rbegin(); iter--)
			PRINT(*iter);
		for (Local::const_reverse_iterator iter = --m0.rend(); iter != m0.rbegin(); iter--)
			PRINT(*iter);

		PRINT("%%> 4 :: erasing <%%");

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
		while (m0.begin() != m0.end())
			m0.erase(m0.begin());
		LOG(m0);
	}
	{
		typedef const OBJ<int> Local;
		PRINT("%%> 5 :: const <%%");

		Local m0;
		m0.begin();
		m0.end();
		m0.rbegin();
		m0.rend();
		m0.empty();
		m0.size();
		m0.max_size();
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
		typedef OBJ<char> Local;
		PRINT("%%> 6 :: non-member <%%");

		Local m0, m1;

		PRINT(std::boolalpha << (m0 == m1));
		PRINT(std::boolalpha << (m0 != m1));
		PRINT(std::boolalpha << (m0 < m1));
		PRINT(std::boolalpha << (m0 > m1));
		PRINT(std::boolalpha << (m0 <= m1));
		PRINT(std::boolalpha << (m0 >= m1));

		m0.insert('a');
		PRINT("");
		m1.insert('b');

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
		typedef OBJ<int> Local;
		PRINT("%%> 7 :: performance <%%");

		Local	v0;
		Local	v1;
		Local::iterator	it;
		const size_t size = 10000000;

		for (size_t i = 0; i < size; i++)
			v0.insert(i);
		v1.insert(v0.begin(), v0.end());
		for (size_t i = 0; i < size / 2; i++)
		{
			v0.lower_bound(*v0.find(i));
			v0.upper_bound(*v0.find(i));
			v0.equal_range(*v0.find(i));
		}
		for (size_t i = 0; i < size; i++)
			v0.erase(v0.begin());
		v1.erase(v1.begin(), v1.end());
	}
	return (0);
}
