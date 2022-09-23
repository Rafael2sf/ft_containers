#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include "stack.hpp"

#define LOG(X) { stack_info(X); }
#define PRINT(X) { std::cout << X << std::endl; }

template <class T>
void
stack_info( T const& __s )
{
	if (__s.empty())
	{
		std::cout << "[ empty ]" << std::endl;
		return ;
	}
	std::cout << " ";
	std::cout << "top = " << __s.top();
	std::cout << " ";
	std::cout << "size =" << __s.size();
	std::cout << std::endl;
}

int	main( void )
{
	PRINT("%%> 0 :: all <%%");

	ft::stack< int, std::deque<int> > s0;
	LOG(s0);
	s0.push(1);
	LOG(s0);
	s0.push(2);
	LOG(s0);
	s0.push(3);
	LOG(s0);
	s0.push(4);
	LOG(s0);
	PRINT(s0.top());

	ft::stack< int, std::deque<int> > s1(s0);
	LOG(s1);
	s1.pop();
	s0.push(5);
	s0 = s1;
	LOG(s0);
	s1.pop();
	LOG(s1);
	PRINT(s1.top());

	ft::stack< int, std::list<int> > s2;
	while (s2.size() != 42)
		s2.push(42);
	LOG(s2);
	while (!s2.empty())
	{
		PRINT(s2.top());
		s2.pop();
	}

	std::vector<int> v(100000000, 42);
	ft::stack< int, std::vector<int> > s3(v);
	LOG(s3);
	while (!s3.empty())
		s3.pop();
	while (s3.size() != 100000000)
		s3.push(42);
	LOG(s3);
	s3.pop();

	PRINT(std::boolalpha << (s0 == s1));
	PRINT(std::boolalpha << (s0 != s1));
	PRINT(std::boolalpha << (s0 < s1));
	PRINT(std::boolalpha << (s0 <= s1));
	PRINT(std::boolalpha << (s0 > s1));
	PRINT(std::boolalpha << (s0 >= s1));
	std::swap(s0, s1);
	PRINT(std::boolalpha << (s0 == s1));
	PRINT(std::boolalpha << (s0 != s1));
	PRINT(std::boolalpha << (s0 < s1));
	PRINT(std::boolalpha << (s0 <= s1));
	PRINT(std::boolalpha << (s0 > s1));
	PRINT(std::boolalpha << (s0 >= s1));
	return (0);
}
