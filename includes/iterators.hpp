#pragma once

#include <iterator>
#include <cstddef>

namespace ft
{
	template<class T>
	struct iterator_traits
	{
		typedef typename T::iterator_category	iterator_category;
		typedef typename T::value_type			value_type;
		typedef typename T::difference_type		difference_type;
		typedef typename T::pointer				pointer;
		typedef typename T::reference			reference;
	};

	template<class T>
	struct iterator_traits<T *>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T *								pointer;
		typedef T &								reference;
	};

	template<class T>
	struct iterator_traits<T const *>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T const *						pointer;
		typedef T const &						reference;
	};
}
