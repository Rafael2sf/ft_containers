#include <iostream>
#include "../includes/vector.hpp"
#include <vector>

template<class T>
struct MyAllocator : public std::allocator<T>
{
	typedef typename std::allocator<T>::value_type		value_type;
	typedef typename std::allocator<T>::allocator_type	allocator_type;
	typedef typename std::allocator<T>::reference 		reference;
	typedef typename std::allocator<T>::const_reference	const_reference;
	typedef typename std::allocator<T>::pointer			pointer;
	typedef	typename std::allocator<T>::const_pointer	const_pointer;
	typedef typename std::allocator<T>::size_type		size_type;
	typedef typename std::allocator<T>::difference_type	difference_type;

	pointer allocate( size_type n, const void * hint = 0 )
	{
		std::cout << "[MEM] allocating ( ";
		std::cout << n << " * " << sizeof(T) << " bytes. ";
		std::cout << "{" << n * sizeof(T) << "}" << std::endl;
		return std::allocator<T>::allocate(n, hint);
	}

	void deallocate( pointer p, std::size_t n )
	{
		std::cout << "[MEM] deallocating ( ";
		std::cout << n << " * " << sizeof(T) << " bytes. ";
		std::cout << "{" << n * sizeof(T)<< "}" << std::endl;
	}
};

template<class T>
void	vInfo( std::string const & var, ft::vector<T> const & v )
{
	if (v.empty())
	{
		std::cout << "[Empty Vector]" << std::endl;
		return ;
	}
	std::cout << var;
	std::cout << " = [ " << v.front();
	std::cout << " ... " << v.back() << " ]";
	std::cout<< " size: " << v.size();
	std::cout << " capacity: " << v.capacity();
	std::cout << std::endl;
}

template<class T>
void	vPrint( std::string const & var, ft::vector<T> & v )
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
	return (0);
}
