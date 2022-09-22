#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "RedBlackTree.hpp"
#include "utility.hpp"
#include "algorithm.hpp"

namespace ft
{
	template <class T>
	struct KeyOfUnique : std::unary_function<T, T>
	{
		T operator()(T __x ) const { return __x; }
	};

	template	<class Key,
				class Compare = std::less<Key>,
				class Alloc = std::allocator<Key>
	> class set
	{
		protected:
		typedef ft::RedBlackTree<const Key, Key,
			ft::KeyOfUnique<Key>, Compare, Alloc>	container;
		container	_rb_tree;

		public:
		typedef Key
			key_type;
		typedef Key
			value_type;
		typedef Compare
			key_compare;
		typedef Compare
			value_compare;
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
		typedef typename container::const_iterator
			iterator;
		typedef typename container::const_iterator
			const_iterator;
		typedef typename container::reverse_iterator
			reverse_iterator;
		typedef typename container::const_reverse_iterator
			const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type
			difference_type;

		/* constructors */

		~set()
		{
			_rb_tree.clear();
		}

		explicit
		set( key_compare const& __comp = key_compare(),
			allocator_type const& __alloc = allocator_type() )
		: _rb_tree(__comp, __alloc)
		{}

		template <class InputIterator>
		set( InputIterator __first, InputIterator __last,
			key_compare const& __comp = key_compare(),
			allocator_type const& __alloc = allocator_type() )
		: _rb_tree(__first, __last, __comp, __alloc)
		{}

		set( set const& __other )
		: _rb_tree(__other.begin(), __other.end(),
			key_compare(), allocator_type())
		{}

		set &
		operator=( set const& __rhs )
		{
			_rb_tree = __rhs._rb_tree;
			return *this;
		}

		value_compare
		value_comp( void ) const
		{
			return value_compare();
		}

		key_compare
		key_comp( void ) const
		{
			return key_compare();
		}

		allocator_type
		get_allocator( void ) const
		{
			return allocator_type();
		}

		void
		swap( set & __other )
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

		reverse_iterator
		rbegin( void )
		{
			return _rb_tree.rbegin();
		}

		const_reverse_iterator
		rbegin( void ) const
		{
			return _rb_tree.rbegin();
		}

		reverse_iterator
		rend( void )
		{
			return _rb_tree.rend();
		}

		const_reverse_iterator
		rend( void ) const
		{
			return _rb_tree.rend();
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

		ft::pair<iterator, bool>
		insert( value_type const& __val )
		{
			return _rb_tree.insert(__val);
		}

		iterator
		insert( iterator __position, value_type const& __val )
		{
			return (_rb_tree.insert(__position._N_const_cast(), __val));
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
			_rb_tree.erase(__pos._N_const_cast());
		}

		size_type
		erase( key_type const& __key )
		{
			return _rb_tree.erase(__key);
		}

		void
		erase(iterator __first, iterator __last)
		{
			_rb_tree.erase(__first._N_const_cast(), __last._N_const_cast());
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

		ft::pair<iterator, iterator>
		equal_range( key_type const& __key )
		{
			return _rb_tree.equal_range(__key);
		}

		ft::pair<const_iterator, const_iterator>
		equal_range( key_type const& __key ) const
		{
			return _rb_tree.equal_range(__key);
		}
	};

	template< class T, class Compare, class Alloc >
	bool
	operator==( ft::set<T,Compare,Alloc> const& __lhs,
				ft::set<T,Compare,Alloc> const& __rhs )
	{
		if (__lhs.size() != __rhs.size())
			return (false);
		return ft::equal(__lhs.begin(), __lhs.end(), __rhs.begin());
	}

	template< class T, class Compare, class Alloc >
	bool
	operator<( ft::set<T,Compare,Alloc> const& __lhs,
				ft::set<T,Compare,Alloc> const& __rhs )
	{
		return ft::lexicographical_compare(__lhs.begin(),
			 __lhs.end(), __rhs.begin(), __rhs.end());
	}

	template< class T, class Compare, class Alloc >
	bool
	operator!=( ft::set<T,Compare,Alloc> const& __lhs,
				ft::set<T,Compare,Alloc> const& __rhs )
	{
		return !(__lhs == __rhs);
	}

	template< class T, class Compare, class Alloc >
	bool
	operator>( ft::set<T,Compare,Alloc> const& __lhs,
				ft::set<T,Compare,Alloc> const& __rhs )
	{
		return __rhs < __lhs;
	}

	template< class T, class Compare, class Alloc >
	bool
	operator<=( ft::set<T,Compare,Alloc> const& __lhs,
				ft::set<T,Compare,Alloc> const& __rhs )
	{
		return !(__rhs < __lhs);
	}

	template< class T, class Compare, class Alloc >
	bool
	operator>=( ft::set<T,Compare,Alloc> const& __lhs,
				ft::set<T,Compare,Alloc> const& __rhs )
	{
		return !(__lhs < __rhs);
	}

	template< class T, class Compare, class Alloc >
	void
	swap( ft::set<T,Compare,Alloc>& __x,
		ft::set<T,Compare,Alloc>& __y )
	{
		__x.swap(__y);
	}
};

#endif
