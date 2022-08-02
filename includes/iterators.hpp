#pragma once

#include <iterator>
#include <cstddef>

namespace ft
{
	template<class I>
	class iterator_traits
	{
		typedef typename I::iterator_category	iterator_category;
		typedef typename I::value_type			value_type;
		typedef typename I::difference_type		difference_type;
		typedef typename I::pointer				pointer;
		typedef typename I::reference			reference;
	};

	template<class I>
	class iterator_traits<I *>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef I								value_type;
		typedef ptrdiff_t						difference_type;
		typedef I *								pointer;
		typedef I &								reference;
	};

	template<class I>
	class iterator_traits<I const *>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef I								value_type;
		typedef ptrdiff_t						difference_type;
		typedef I const *						pointer;
		typedef I const &						reference;
	};
}
