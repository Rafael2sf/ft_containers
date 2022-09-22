#include <iostream>
#include <vector>
#include "../includes/vector.hpp"

#define PRINT(X) { std::cout << X << std::endl; }
#define INFO(X) { vector_info(X); }
#define ITER(X) { vector_iter(X); }
#define LOG(X) { vector_info(X); vector_iter(X); }
#define OBJ ft::vector

template<class T>
void	vector_info( T const& v )
{
	if (v.empty())
		std::cout << "[ empty ]";
	else
	{
		std::cout << "[ " << v.front();
		std::cout << " ... " << v.back() << " ]";
	}
	std::cout << " size: " << v.size();
	std::cout << " capacity: " << v.capacity();
	std::cout << std::endl;
}

template<class T>
void	vector_iter( T const& v )
{
	typename T::const_iterator it = v.begin();

	std::cout << "{ ";
	while(it != v.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << "}" << std::endl;
}

int	main( void )
{
	// {
	// 	typedef OBJ<int> Local;
	// 	PRINT("%%> 0 :: constructors <%%");

	// 	Local v0;

	// 	LOG(v0);
	// 	Local v1(5, 42);
	// 	LOG(v1);
	// 	Local v2(v1);
	// 	LOG(v2);
	// 	Local v3(v2.begin() + 1, v2.end() - 1);
	// 	LOG(v3);
	// 	Local v4;
	// 	v4 = v2;
	// 	v2.push_back(0);
	// 	LOG(v4);
	// }
	// {
	// 	typedef OBJ<std::string> Local;
	// 	PRINT("%%> 1 :: CAPACITY <%%");

	// 	Local	v0;

	// 	PRINT((v0.empty() ? "v0 is empty" : "v0 is not empty"))
	// 	v0.reserve(1);
	// 	for (int i = 1; i < 10; i++)
	// 		v0.push_back("hello world");
	// 	LOG(v0);
	// 	v0.resize(5);
	// 	LOG(v0);
	// 	v0.resize(100, "resize it is!");
	// 	v0.reserve(32);
	// 	LOG(v0);
	// 	PRINT("v0.max_size() == " << v0.max_size());
	// 	PRINT((v0.empty() ? "v0 is empty" : "v0 is not empty"));
	// }
	// {
	// 	typedef OBJ<double> Local;
	// 	std::cout << "%%> 2 :: access <%%" << std::endl;

	// 	Local	v0;

	// 	for (int i = 0; i < 10; i++)
	// 		v0.push_back(42.42 + i);
	// 	PRINT(v0[1]);
	// 	v0[1] = 420;
	// 	PRINT(v0[1]);
	// 	PRINT(v0.front());
	// 	PRINT(v0.back());
	// 	PRINT(v0.at(5));
	// 	PRINT(v0.at(0));
	// 	PRINT(v0.at(v0.size() - 1));
	// 	PRINT(*v0.data());
	// }
	// {
	// 	typedef OBJ<char> Local;
	// 	PRINT("%%> 3 :: modifiers <%%");

	// 	Local	v0;
	// 	Local	v1;

	// 	for (int i = 0; i < 26; i++)
	// 		v0.push_back('a' + i);
	// 	LOG(v0);
	// 	v1.insert(v1.begin(), '4');
	// 	ITER(v1);
	// 	v1.insert(v1.end(), '2');
	// 	ITER(v1);
	// 	v1.insert(v1.end() - 1, 10, 'x');
	// 	ITER(v1);
	// 	v1.insert(v1.begin(), v0.begin(), v0.end());
	// 	LOG(v1);
	// 	PRINT(*v0.erase(v0.end() - 1));
	// 	PRINT(*v0.erase(v0.begin()));
	// 	PRINT(*v0.erase(v0.begin() + v0.size() / 2));
	// 	LOG(v0);
	// 	std::cout << *v1.erase(v1.begin() + 1, v1.begin() + 26) << std::endl;
	// 	LOG(v1);
	// 	v1.clear();
	// 	LOG(v1);
	// 	v1 = v0;
	// 	LOG(v1);
	// 	v1.erase(v1.begin(), v1.end());
	// 	LOG(v1);
	// 	v1.swap(v0);
	// 	ITER(v0);
	// 	ITER(v1);
	// 	v1.assign(10, 100);
	// 	LOG(v1);
	// 	v1.assign(v1.begin(), v1.end());
	// 	LOG(v1);
	// 	while (v0.size())
	// 		v0.pop_back();
	// 	LOG(v0);
	// }
	// /* extra */
	// {
	// 	std::cout << "%%> 4 :: other <%%" << std::endl;
	// 	typedef OBJ<int> Local;

	// 	Local v0;
	// 	Local v1;

	// 	v0.get_allocator();
	// 	for (int i = 0; i < 42; i++)
	// 		v0.push_back(i);
	// 	LOG(v0);
	// 	LOG(v1);
	// 	v1.push_back(1);
	// 	PRINT(std::boolalpha << (v0 == v1));
	// 	PRINT(std::boolalpha << (v0 != v1));
	// 	PRINT(std::boolalpha << (v0 < v1));
	// 	PRINT(std::boolalpha << (v0 <= v1));
	// 	PRINT(std::boolalpha << (v0 > v1));
	// 	PRINT(std::boolalpha << (v0 >= v1));
	// 	v0.swap(v1);
	// 	LOG(v0);
	// 	LOG(v1);
	// 	PRINT(std::boolalpha << (v0 == v1));
	// 	PRINT(std::boolalpha << (v0 != v1));
	// 	PRINT(std::boolalpha << (v0 < v1));
	// 	PRINT(std::boolalpha << (v0 <= v1));
	// 	PRINT(std::boolalpha << (v0 > v1));
	// 	PRINT(std::boolalpha << (v0 >= v1));
	// }
	// {
	// 	typedef OBJ<char> Local;
	// 	PRINT("%%> 5 :: iterators <%%");

	// 	Local	v0;
	// 	Local	v1;
	// 	Local::iterator	it;
	// 	Local::const_iterator	cit;
	// 	Local::reverse_iterator	rit;
	// 	Local::const_reverse_iterator	rcit;

	// 	for (int i = 0; i < 26; i++)
	// 		v0.push_back('a' + i);
	// 	for (it = v0.begin(); it != v0.end(); it++)
	// 		PRINT(*it);
	// 	for (cit = v0.begin(); cit != v0.end(); cit++)
	// 		PRINT(*cit);
	// 	for (rit = v0.rbegin(); rit != v0.rend(); rit++)
	// 		PRINT(*rit);
	// 	for (rcit = v0.rbegin(); rcit != v0.rend(); rcit++)
	// 		PRINT(*rcit);

	// 	it = --v0.begin();
	// 	if (it == v0.end())
	// 		PRINT("iter = END")
	// 	it = v0.end();
	// 	++it;
	// 	if (it != v0.end())
	// 	{
	// 		PRINT(*it);
	// 		*it = 42;
	// 	}
	// 	it = v0.begin();
	// 	cit = v0.begin() + 1;
	// 	PRINT(*cit);
	// 	cit = it;
	// 	PRINT(*cit);

	// 	(it == cit);
	// 	(cit == it);
	// 	(it < cit);
	// 	(cit < it);

	// 	for (it = --v0.end(); it != v0.begin(); it--)
	// 		PRINT(*it);
	// 	for (cit = --v0.end(); cit != v0.begin(); cit--)
	// 		PRINT(*cit);
	// 	for (rit = --v0.rend(); rit != v0.rbegin(); rit--)
	// 		PRINT(*rit);
	// 	for (rcit = --v0.rend(); rcit != v0.rbegin(); rcit--)
	// 		PRINT(*rcit);
	// }
	// {
	// 	typedef const OBJ<int> Local;
	// 	PRINT("%%> 6 :: const <%%");

	// 	ft::vector<int> x(10, 420);

	// 	Local v0;
	// 	try { v0.at(42); } catch ( std::exception & ) {}
	// 	v0.front();
	// 	v0.back();
	// 	v0.data();
	// 	v0.begin();
	// 	v0.end();
	// 	v0.rbegin();
	// 	v0.rend();
	// 	v0.empty();
	// 	v0.size();
	// 	v0.capacity();
	// 	v0.max_size();
	// }
	{
		typedef OBJ<int> Local;
		PRINT("%%> 7 :: performance <%%");

		Local	v0;
		// /const size_t size = 1000000;

		v0.assign(20000000, 42);

		for (size_t i = 0; i < 10000; i++)
		{
			std::cout << i << std::endl;
			v0.insert(v0.begin(), 1, i);
		}
		//LOG(v0);
		// for (size_t i = 0; i < size; i++)
		// 	v0.pop_back();
		// v0.insert(v0.begin(), size, 0);
		// v0.assign(size * 2, 0);
		// v0.erase(v0.begin(), v0.end());
	}
	return (0);
}
