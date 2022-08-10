#include <iostream>
#include "../includes/vector.hpp"
#include <vector>

template<class T>
struct MyAllocator : public std::allocator<T>
{
	typedef typename std::allocator<T>::value_type		value_type;
	typedef typename std::allocator<T>::reference 		reference;
	typedef typename std::allocator<T>::const_reference	const_reference;
	typedef typename std::allocator<T>::pointer			pointer;
	typedef	typename std::allocator<T>::const_pointer	const_pointer;
	typedef typename std::allocator<T>::size_type		size_type;
	typedef typename std::allocator<T>::difference_type	difference_type;

	pointer allocate( size_type n, const void * hint = 0 )
	{
		std::cout << "[MEM] allocating ( ";
		std::cout << n << " * " << sizeof(T) << " bytes) ";
		std::cout << "{" << n * sizeof(T) << "}" << std::endl;
		return std::allocator<T>::allocate(n, hint);
	}

	void deallocate( pointer p, std::size_t n )
	{
		std::cout << "[MEM] deallocating ( ";
		std::cout << n << " * " << sizeof(T) << " bytes) ";
		std::cout << "{" << n * sizeof(T)<< "}" << std::endl;
		std::allocator<T>::deallocate(p, n);
	}
};

template<class T, class Alloc >
void	vInfo( std::string const & var, ft::vector<T, Alloc> const & v )
{
	if (v.empty())
	{
		std::cout << var << " = [ ]" << std::endl;
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

template<class T, class Alloc >
void	vPrint( std::string const & var, ft::vector<T, Alloc> & v )
{
	typename ft::vector<T, Alloc>::iterator it = v.begin();

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
		ft::vector<int>	v0;
		ft::vector<int>	v1(5, 42);
		ft::vector<int>	v2(v1);
		ft::vector<int>	v3;
		v3 = v2;
		v2.push_back(0);
		vInfo<int>("v0", v0);
		vInfo<int>("v1", v1);
		vInfo<int>("v2", v2);
		vPrint<int>("v3", v3);
	}
	/* capacity related */
	std::cout << "%% TEST 1 :: CAPACITY %%" << std::endl;
	{
		ft::vector<float, MyAllocator<float> >	v0;
		std::cout << (v0.empty() ? "v0 is empty" : "v0 is not empty") << std::endl;
		v0.reserve(1);
		for (int i = 1; i < 10; i++)
			v0.push_back(i + 0.5);
		vInfo<float, MyAllocator<float> >("v0", v0);
		vPrint<float, MyAllocator<float> >("v0", v0);
		v0.resize(5, 42);
		vInfo<float, MyAllocator<float> >("v0", v0);
		vPrint<float, MyAllocator<float> >("v0", v0);
		v0.resize(100);
		v0.reserve(32);
		vInfo<float, MyAllocator<float> >("v0", v0);
		vPrint<float, MyAllocator<float> >("v0", v0);
		std::cout << "v0.max_size() == " << v0.max_size() << std::endl;
		std::cout << (v0.empty() ? "v0 is empty" : "v0 is not empty") << std::endl;
	}
	/* element acess */
	// std::cout << "%% TEST 2 :: ACCESS %%" << std::endl;
	// {
	// 	ft::vector<std::string>	v0;
	// }
	return (0);
}
