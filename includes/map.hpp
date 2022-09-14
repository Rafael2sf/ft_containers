#pragma once

#include "RedBlackTree.hpp"

namespace ft
{
	template	<class Key,
				class T,
				class Compare = std::less<Key>,
				class Alloc = std::allocator<pair<const Key,T> >
	> class map
	{
		protected:

		typedef RedBlackTree<const Key, T, Compare, Alloc>	container;

		public:

		typedef Key
			key_type;
		typedef T
			mapped_type;
		typedef pair<const key_type, mapped_type>
			value_type;
		typedef Compare
			key_compare;
		//typedef Compare
		// value_compare;
		typedef Alloc
			allocator_type;
		typedef typename allocator_type::reference
			reference;
		typedef typename allocator_type::const_reference
			const_reference;
		typedef typename allocator_type::pointer
			pointer;
		typedef typename allocator_type::const_pointer	
			const_pointer;
		typedef size_t
			size_type;
		typedef typename container::iterator
			iterator;
		typedef typename container::const_iterator
			const_iterator;
		typedef typename container::reverse_iterator
			reverse_iterator;
		typedef typename container::const_reverse_iterator
			const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type
			difference_type;

		private:

		container	_rb_tree;

		public:

		~map()
		{}

		map( void )
		: _rb_tree()
		{}
	};
};
