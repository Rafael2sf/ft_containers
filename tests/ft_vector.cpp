#include <iostream>
#include "../includes/vector.hpp"
#include <vector>

template<class T>
void	vInfo( std::string const& var, ft::vector<T> const& v )
{
	if (v.empty())
	{
		std::cout << var << " = [ ]";
	}
	else
	{
		std::cout << var;
		std::cout << " = [ " << v.front();
		std::cout << " ... " << v.back() << " ]";
	}
	std::cout<< " size: " << v.size();
	std::cout << " capacity: " << v.capacity();
	std::cout << std::endl;
}

template<class T>
void	vPrint( std::string const& var, ft::vector<T> & v )
{
	typename ft::vector<T>::iterator it = v.begin();

	std::cout << var << " = { ";
	while(it != v.end())
		std::cout << *it++ << " ";
	std::cout << "}" << std::endl;
}

int	main( void )
{
	/* Constructors */
	std::cout << "%% TEST 0 :: CONSTRUCTORS %%" << std::endl;
	{
		ft::vector<int> v0;
		ft::vector<int> v1(5, 42);
		ft::vector<int> v2(v1);
		ft::vector<int> v3(v2.begin() + 1, v2.end() - 1);
		ft::vector<int> v4;
		v4 = v2;
		v2.push_back(0);
		vInfo<int>("v0", v0);
		vInfo<int>("v1", v1);
		vInfo<int>("v2", v2);
		vInfo<int>("v3", v3);
		vPrint<int>("v3", v3);
		vPrint<int>("v4", v4);
		vInfo<int>("v4", v4);
	}
	/* capacity related */
	std::cout << "%% TEST 1 :: CAPACITY %%" << std::endl;
	{
		ft::vector<std::string>	v0;
		std::cout << (v0.empty() ? "v0 is empty" : "v0 is not empty") << std::endl;
		v0.reserve(1);
		for (int i = 1; i < 10; i++)
			v0.push_back("hello world");
		vInfo<std::string>("v0", v0);
		vPrint<std::string>("v0", v0);
		v0.resize(5);
		vInfo<std::string>("v0", v0);
		vPrint<std::string>("v0", v0);
		v0.resize(100, "resize it is!");
		v0.reserve(32);
		vInfo<std::string>("v0", v0);
		vPrint<std::string>("v0", v0);
		std::cout << "v0.max_size() == " << v0.max_size() << std::endl;
		std::cout << (v0.empty() ? "v0 is empty" : "v0 is not empty") << std::endl;
	}
	/* element acess */
	std::cout << "%% TEST 2 :: ACCESS %%" << std::endl;
	{
		ft::vector<double>	v0;
		for (int i = 0; i < 10; i++)
			v0.push_back(42.42 + i);
		std::cout << v0[1] << std::endl;
		v0[1] = 420;
		std::cout << v0[1] << std::endl;
		std::cout << v0.front() << std::endl;
		std::cout << v0.back() << std::endl;
		std::cout << v0.at(5) << std::endl;
		std::cout << v0.at(0) << std::endl;
		std::cout << v0.at(v0.size() - 1) << std::endl;
		std::cout << *v0.data() << std::endl;
	}
	/* modifiers */
	std::cout << "%% TEST 3 :: MODIFIERS %%" << std::endl;
	{
		ft::vector<char>	v0;
		ft::vector<char>	v1;

		for (int i = 0; i < 26; i++)
			v0.push_back('a' + i);
		vInfo<char>("v0", v0);
		v1.insert(v1.begin(), '4');
		vPrint<char>("v1", v1);
		v1.insert(v1.end(), '2');
		vPrint<char>("v1", v1);
		v1.insert(v1.end() - 1, 10, 'x');
		vPrint<char>("v1", v1);
		v1.insert(v1.begin(), v0.begin(), v0.end());
		vPrint<char>("v1", v1);
		std::cout << *v0.erase(v0.end() - 1) << std::endl;
		std::cout << *v0.erase(v0.begin()) << std::endl;
		std::cout << *v0.erase(v0.begin() + v0.size() / 2) << std::endl;
		vPrint<char>("v0", v0);
		std::cout << *v1.erase(v1.begin() + 1, v1.begin() + 26) << std::endl;
		vPrint<char>("v1", v1);
		v1.clear();
		vPrint<char>("v1", v1);
		v1 = v0;
		vPrint<char>("v1", v1);
		v1.erase(v1.begin(), v1.end());
		vPrint<char>("v1", v1);
		v1.swap(v0);
		vPrint<char>("v1", v1);
		v1.assign(10, 100);
		vPrint<char>("v1", v1);
		v1.assign(v1.begin(), v1.end());
		vPrint<char>("v1", v1);
		while (v0.size())
			v0.pop_back();
		vPrint<char>("v0", v0);
	}
	/* extra */
	std::cout << "%% TEST 4 :: EXTRA %%" << std::endl;
	{
		ft::vector<int> v0;
		ft::vector<int> v1;
		v0.get_allocator();
		for (int i = 0; i < 42; i++)
			v0.push_back(i);
		vPrint<int>("v0", v0);
		vPrint<int>("v1", v1);
		v1.push_back(1);
		std::cout << "== is " << (v0 == v1 ? "true" : "false") << std::endl;
		std::cout << "!= is " << (v0 != v1 ? "true" : "false") << std::endl;
		std::cout << "< is " << (v0 < v1 ? "true" : "false") << std::endl;
		std::cout << "<= is " << (v0 <= v1 ? "true" : "false") << std::endl;
		std::cout << "> is " << (v0 > v1 ? "true" : "false") << std::endl;
		std::cout << ">= is " << (v0 >= v1 ? "true" : "false") << std::endl;
		v0.swap(v1);
		vPrint<int>("v0", v0);
		vPrint<int>("v1", v1);
		std::cout << "== is " << (v0 == v1 ? "true" : "false") << std::endl;
		std::cout << "!= is " << (v0 != v1 ? "true" : "false") << std::endl;
		std::cout << "< is " << (v0 < v1 ? "true" : "false") << std::endl;
		std::cout << "<= is " << (v0 <= v1 ? "true" : "false") << std::endl;
		std::cout << "> is " << (v0 > v1 ? "true" : "false") << std::endl;
		std::cout << ">= is " << (v0 >= v1 ? "true" : "false") << std::endl;
	}
	std::cout << "%% TEST 5 :: ITERATORS %%" << std::endl;
	{
		ft::vector<int>	v0(42, 42);

		ft::vector<int>::iterator it;
		ft::vector<int>::reverse_iterator rit;
		ft::vector<int>::const_iterator cit;
		ft::vector<int>::const_reverse_iterator crit;

		it == cit;

		std::cout << *(it = v0.begin()) << std::endl;
		std::cout << *(it = v0.end() - 1) << std::endl;

		std::cout << *(cit = v0.begin()) << std::endl;
		std::cout << *(cit = v0.end()) << std::endl;

		std::cout << *(rit = v0.rend()) << std::endl;
		std::cout << *(rit = v0.rbegin()) << std::endl;

		std::cout << *(rit = v0.rend()) << std::endl;
		std::cout << *(rit = v0.rbegin()) << std::endl;

		it = v0.begin();
		std::cout << "( ";
		while (it != v0.end())
			std::cout << *it++ << " ";
		std::cout << ")" << std::endl;
		it -= 5;
		std::cout << *it << std::endl;
		it += 1;
		std::cout << *it << std::endl;
		it -= 2;
		std::cout << *it << std::endl;
		--it;
		std::cout << *it << std::endl;
		it[5] = 2;
		std::cout << it[5] << std::endl;
		std::cout << *it.base() << std::endl;

		rit = v0.rbegin();
		std::cout << "( ";
		while (rit != v0.rend())
			std::cout << *rit++ << " ";
		std::cout << ")" << std::endl;
		rit -= 5;
		std::cout << *rit << std::endl;
		rit += 1;
		std::cout << *rit << std::endl;
		rit -= 2;
		std::cout << *rit << std::endl;
		--rit;
		std::cout << *rit << std::endl;
		rit[5] = 42;
		std::cout << rit[5] << std::endl;
		std::cout << *rit.base() << std::endl;
		std::cout << (*v0.end().base() == *v0.rbegin().base()) << std::endl;
	}
	std::cout << "%% TEST 6 :: PERFORMANCE %%" << std::endl;
	{
		const size_t size = 1000000;
		ft::vector<int>	v0;

		for (size_t i = 0; i < size; i++)
			v0.push_back(i);
		for (size_t i = 0; i < size; i++)
			v0.pop_back();
		vInfo<int>("v0", v0);
		v0.insert(v0.begin(), size, 0);
		vInfo<int>("v0", v0);
		v0.assign(size * 2, 0);
		vInfo<int>("v0", v0);
		v0.erase(v0.begin(), v0.end());
		vInfo<int>("v0", v0);
	}
	return (0);
}
