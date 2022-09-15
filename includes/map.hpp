#pragma once

#include <functional>
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
		container	_rb_tree;

		public:

		typedef Key
			key_type;
		typedef T
			mapped_type;
		typedef pair<const key_type, mapped_type>
			value_type;
		typedef Compare
			key_compare;
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

		public:

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;

			protected:

			Compare comp;
			value_compare( Compare c ) : comp(c) {}

			public:

			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			bool
			operator() ( value_type const& x, value_type const& y ) const
			{
				return comp(x.first, y.first);
			}
		};

		/* constructors */

		~map()
		{
			_rb_tree.clear();
		}

		explicit
		map( key_compare const& __comp = key_compare(),
			allocator_type const& __alloc = allocator_type() )
		: _rb_tree(__comp, __alloc)
		{}

		template <class InputIterator>
		map( InputIterator __first, InputIterator __last,
			key_compare const& __comp = key_compare(),
			allocator_type const& __alloc = allocator_type() )
		: _rb_tree(__first, __last, __comp, __alloc)
		{}

		map( map const& __other )
		: _rb_tree(__other.begin(), __other.end(),
			key_compare(), allocator_type())
		{}

		map &
		operator=( map const& __rhs )
		{
			_rb_tree = __rhs._rb_tree;
			return *this;
		}

		mapped_type &
		operator[]( Key const& __key )
		{
			return (_rb_tree[__key]);
		}

		mapped_type &
		at( key_type const& __key )
		{
			try
			{
				return _rb_tree.at(__key);
			}
			catch ( std::exception & )
			{
				throw std::out_of_range("map::at");
			}
		}

		mapped_type const&
		at( key_type const& __key ) const
		{
			try
			{
				return _rb_tree.at(__key);
			}
			catch ( std::exception & )
			{
				throw std::out_of_range("map::at");
			}
		}

		void
		swap( map & __other )
		{
			_rb_tree.swap(__other._rb_tree);
		}

		/* iterators */

		iterator
		begin( void )
		{
			return _rb_tree.begin();
		}

		const_iterator
		begin( void ) const
		{
			return _rb_tree.begin();
		}

		iterator
		end( void )
		{
			return _rb_tree.end();
		}

		const_iterator
		end( void ) const
		{
			return _rb_tree.end();
		}

		/* capacity */

		bool
		empty( void ) const
		{
			return _rb_tree.empty();
		}

		size_type
		size( void ) const
		{
			return _rb_tree.size();
		}

		size_type
		max_size( void ) const
		{
			return _rb_tree.max_size();
		}

		/* modifiers */

		pair<iterator, bool>
		insert( value_type const& __val )
		{
			return _rb_tree.insert(__val);
		}

		iterator
		insert( iterator __position, value_type const& __val )
		{
			return (_rb_tree.insert(__position, __val));
		}

		template <class InputIterator>
		void
		insert(InputIterator __first, InputIterator __last )
		{
			_rb_tree.insert(__first, __last);
		}

		void
		erase( iterator __pos )
		{
			_rb_tree.erase(__pos);
		}

		size_type
		erase( key_type const& __key )
		{
			return _rb_tree.erase(__key);
		}

		void
		erase(iterator __first, iterator __last)
		{
			_rb_tree.erase(__first, __last);
		}

		void
		clear( void )
		{
			_rb_tree.clear();
		}

		/* operations */

		iterator
		find( key_type const& __key )
		{
			return _rb_tree.find(__key);
		}

		const_iterator
		find( key_type const& __key ) const
		{
			return _rb_tree.find(__key);
		}

		size_type
		count( key_type const& __key ) const
		{
			return _rb_tree.count(__key);
		}

		iterator
		lower_bound( key_type const& __key )
		{
			return _rb_tree.lower_bound(__key);
		}

		const_iterator
		lower_bound( key_type const& __key ) const
		{
			return _rb_tree.lower_bound(__key);
		}

		iterator
		upper_bound( key_type const& __key )
		{
			return _rb_tree.upper_bound(__key);
		}

		const_iterator
		upper_bound( key_type const& __key ) const
		{
			return _rb_tree.upper_bound(__key);
		}

		pair<iterator, iterator>
		equal_range( key_type const& __key )
		{
			return _rb_tree.equal_range(__key);
		}

		pair<const_iterator, const_iterator>
		equal_range( key_type const& __key ) const
		{
			return _rb_tree.equal_range(__key);
		}
	};
};
