#include <iostream>
#include <stack>
#include <vector>
#include "../includes/stack.hpp"
#include "../includes/vector.hpp"

#define LOG(X) { stack_info(X); }
#define PRINT(X) { std::cout << X << std::endl; }
#define OBJ ft::stack

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
	typedef OBJ<std::string, std::vector<std::string> > Local;
	PRINT("%%> 0 :: all <%%");
	Local	s1;

	LOG(s1);
	s1.push("a");
	LOG(s1);
	s1.push("bb");
	LOG(s1);
	s1.push("ccc");
	LOG(s1);
	s1.push("dddd");
	LOG(s1);

	Local	s2(s1);
	LOG(s2);
	
	Local	s3;
	s3 = s2;
	LOG(s2);

	s3.pop();
	LOG(s1);
	LOG(s2);
	LOG(s3);

	while (!s3.empty())
	{
		s3.pop();
		LOG(s3);
	}

	std::vector<int> v(100000000, 42);
	OBJ<int, std::vector<int> > s4(v);
	LOG(s4);
	while (!s4.empty())
		s4.pop();
	while (s4.size() != 100000000)
		s4.push(42);
	LOG(s4);

	s1.pop();
	PRINT(std::boolalpha << (s1 == s2));
	PRINT(std::boolalpha << (s1 != s2));
	PRINT(std::boolalpha << (s1 < s2));
	PRINT(std::boolalpha << (s1 <= s2));
	PRINT(std::boolalpha << (s1 > s2));
	PRINT(std::boolalpha << (s1 >= s2));
	std::swap(s1, s2);
	PRINT(std::boolalpha << (s1 == s2));
	PRINT(std::boolalpha << (s1 != s2));
	PRINT(std::boolalpha << (s1 < s2));
	PRINT(std::boolalpha << (s1 <= s2));
	PRINT(std::boolalpha << (s1 > s2));
	PRINT(std::boolalpha << (s1 >= s2));

	return (0);
}
