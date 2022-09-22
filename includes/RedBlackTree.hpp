#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include <memory>
#include <functional>
#include <stdexcept>
#include "iterators.hpp"
#include "utility.hpp"
#include "type_traits.hpp"

namespace ft
{
	enum RbColor {
		red = 0,
		black = 1,
		double_black = 2
	};

	struct RbBaseNode
	{
		RbColor		color;
		RbBaseNode	*left;
		RbBaseNode	*right;
		RbBaseNode	*parent;

		static RbBaseNode *
		min( RbBaseNode * __n )
		{
			while (__n->left)
				__n = __n->left;
			return __n;
		}

		static RbBaseNode *
		min( RbBaseNode const* __n )
		{
			while (__n->left)
				__n = __n->left;
			return const_cast<RbBaseNode *>(__n);
		}
	
		static RbBaseNode *
		max( RbBaseNode * __n )
		{
			while (__n->right)
				__n = __n->right;
			return __n;
		}

		static RbBaseNode *
		max( RbBaseNode const* __n )
		{
			while (__n->right)
				__n = __n->right;
			return const_cast<RbBaseNode *>(__n);
		}
	};

	template <class T>
	class RbNode : public RbBaseNode
	{
		public:

		T data;

		~RbNode() {};

		RbNode( void )
		: RbBaseNode()
		{}

		RbNode( T const& __val )
		: RbBaseNode(), data(__val)
		{}

		RbNode( RbNode const& __other )
		: RbBaseNode(), data(__other.data)
		{
			color = __other.color;
			left = __other.left;
			right = __other.right;
			parent = __other.parent;
		}

		RbNode &
		operator=( RbNode const& __rhs )
		{
			data = __rhs.data;
			left = __rhs.left;
			right = __rhs.right;
			parent = __rhs.parent;
			color = __rhs.color;
			return *this;
		}
	};

	template <class T>
	class rb_tree_iterator: public ft::iterator_traits<T*>
	{
		public:

		typedef std::bidirectional_iterator_tag						iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type		value_type;
		typedef typename ft::iterator_traits<T*>::reference			reference;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;

		protected:

		typedef RbBaseNode				base_node;
		typedef RbBaseNode *			base_node_pointer;
		typedef RbNode<value_type>		node;
		typedef RbNode<value_type> *	node_pointer;

		public:

		base_node_pointer _N_;

		rb_tree_iterator( void )
		{}

		explicit rb_tree_iterator( base_node_pointer __p )
		: _N_(__p)
		{}

		rb_tree_iterator( rb_tree_iterator const& __other )
		: _N_(__other._N_)
		{}

		rb_tree_iterator &
		operator=( rb_tree_iterator const& __rhs )
		{
			_N_ = __rhs._N_;
			return *this;
		}

		typename ft::remove_pointer<pointer>::type &
		operator*( void )
		{
			return static_cast<node_pointer>(_N_)->data;
		}

		pointer
		operator->( void )
		{
			return &static_cast<node_pointer>(_N_)->data;
		}

		rb_tree_iterator	&
		operator++( void )
		{
			base_node_pointer	tmp;

			if (_N_->right)
			{
				_N_ = _N_->right;
				while (_N_->left)
					_N_ = _N_->left;
			}
			else
			{
				tmp = _N_->parent;
				if (!tmp)
				{
					_N_ = _N_->max(_N_->left);
					return *this;
				}
				while (tmp->parent && _N_ == tmp->right)
				{
					_N_ = tmp;
					tmp = tmp->parent;
				}
				if (_N_->right != tmp)
					_N_ = tmp;
			}
			return *this;
		}

		rb_tree_iterator 
		operator++( int )
		{
			rb_tree_iterator	it(*this);

			++(*this);
			return (it);
		}

		rb_tree_iterator	&
		operator--( void )
		{
			base_node_pointer	tmp;

			if (_N_->left)
			{
				_N_ = _N_->left;
				while (_N_->right)
					_N_ = _N_->right;
			}
			else
			{
				tmp = _N_->parent;
				while (tmp && tmp->parent && _N_ == tmp->left)
				{
					_N_ = tmp;
					tmp = tmp->parent;
				}
				if (_N_->left != tmp)
					_N_ = tmp;
			}
			return *this;
		}

		rb_tree_iterator
		operator--( int )
		{
			rb_tree_iterator	it(*this);

			--(*this);
			return (it);
		}
	};

	template <class T>
	class rb_tree_const_iterator: public ft::iterator_traits<const T*>
	{
		public:

		typedef std::bidirectional_iterator_tag							iterator_category;
		typedef typename ft::iterator_traits<const T*>::value_type		value_type;
		typedef typename ft::iterator_traits<const T*>::reference		reference;
		typedef typename ft::iterator_traits<const T*>::pointer			pointer;
		typedef typename ft::iterator_traits<const T*>::difference_type	difference_type;

		protected:

		typedef RbBaseNode			base_node;
		typedef RbBaseNode 	*		base_node_pointer;
		typedef RbNode<const T>		node;
		typedef RbNode<const T> *	node_pointer;

		public:

		base_node_pointer _N_;

		rb_tree_const_iterator( void )
		{}

		explicit rb_tree_const_iterator( base_node_pointer __p )
		: _N_(__p)
		{}

		rb_tree_const_iterator( rb_tree_const_iterator const& __other )
		: _N_(__other._N_)
		{}

		template <class U>
		rb_tree_const_iterator( ft::rb_tree_iterator<U> const& __other )
		: _N_(__other._N_)
		{}

		ft::rb_tree_iterator<T>
		_N_const_cast( void )
		{
			return ft::rb_tree_iterator<T>(_N_);
		}

		rb_tree_const_iterator &
		operator=( rb_tree_const_iterator const& __rhs )
		{
			_N_ = __rhs._N_;
			return *this;
		}

		typename ft::remove_pointer<pointer>::type &
		operator*( void )
		{
			return static_cast<node_pointer>(_N_)->data;
		}

		pointer
		operator->( void )
		{
			return &static_cast<node_pointer>(_N_)->data;
		}

		rb_tree_const_iterator	&
		operator++( void )
		{
			base_node_pointer	tmp;

			if (_N_->right)
			{
				_N_ = _N_->right;
				while (_N_->left)
					_N_ = _N_->left;
			}
			else
			{
				tmp = _N_->parent;
				if (!tmp)
				{
					_N_ = _N_->max(_N_->left);
					return *this;
				}
				while (tmp->parent && _N_ == tmp->right)
				{
					_N_ = tmp;
					tmp = tmp->parent;
				}
				if (_N_->right != tmp)
					_N_ = tmp;
			}
			return *this;
		}

		rb_tree_const_iterator 
		operator++( int )
		{
			rb_tree_const_iterator	it(*this);

			++(*this);
			return (it);
		}

		rb_tree_const_iterator	&
		operator--( void )
		{
			base_node_pointer	tmp;

			if (_N_->left)
			{
				_N_ = _N_->left;
				while (_N_->right)
					_N_ = _N_->right;
			}
			else
			{
				tmp = _N_->parent;
				while (tmp && tmp->parent && _N_ == tmp->left)
				{
					_N_ = tmp;
					tmp = tmp->parent;
				}
				if (_N_->left != tmp)
					_N_ = tmp;
			}
			return *this;
		}

		rb_tree_const_iterator
		operator--( int )
		{
			rb_tree_const_iterator	it(*this);

			--(*this);
			return (it);
		}
	};

	template <class Iter1>
	bool
	operator==( ft::rb_tree_const_iterator<Iter1> const& __lhs,
				ft::rb_tree_iterator<Iter1> const&  __rhs )
	{
		return __lhs._N_ == __rhs._N_;
	}

	template <class Iter1>
	bool
	operator!=( ft::rb_tree_const_iterator<Iter1> const& __lhs,
				ft::rb_tree_iterator<Iter1> const&  __rhs )
	{
		return __lhs._N_ != __rhs._N_;
	}

	template <class Iter>
	bool
	operator==( ft::rb_tree_iterator<Iter> const& __lhs,
				ft::rb_tree_iterator<Iter> const&  __rhs )
	{
		return __lhs._N_ == __rhs._N_;
	}

	template <class Iter>
	bool
	operator!=( ft::rb_tree_iterator<Iter> const& __lhs,
				ft::rb_tree_iterator<Iter> const&  __rhs )
	{
		return __lhs._N_ != __rhs._N_;
	}

	template <class Iter>
	bool
	operator==( ft::rb_tree_const_iterator<Iter> const& __lhs,
				ft::rb_tree_const_iterator<Iter> const&  __rhs )
	{
		return __lhs._N_ == __rhs._N_;
	}

	template <class Iter>
	bool
	operator!=( ft::rb_tree_const_iterator<Iter> const& __lhs, 
				ft::rb_tree_const_iterator<Iter> const&  __rhs )
	{
		return __lhs._N_ != __rhs._N_;
	}

	template	<class Key,
				class T,
				class KeyOfValue,
				class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<Key,T> >
	> class RedBlackTree
	{
		public:

		typedef Key
			key_type;
		typedef T
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
		typedef ft::rb_tree_iterator<value_type>
			iterator;
		typedef ft::rb_tree_const_iterator<value_type>
			const_iterator;
		typedef ft::reverse_iterator<iterator>
			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>
			const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type
			difference_type;

		protected:

		typedef RbBaseNode				base_node;
		typedef RbBaseNode *			base_node_pointer;
		typedef RbNode<value_type>		node;
		typedef RbNode<value_type> *	node_pointer;
		typedef typename Alloc::template rebind<RbNode<value_type> >::other
			node_allocator;

		RbNode<size_type>	_head;
		base_node_pointer	_root;
		key_compare			_compare;
		KeyOfValue			_key_of;
		allocator_type		_allocator;
		node_allocator		_node_allocator;

		public:

		~RedBlackTree()
		{
			if (_head.data)
			{
				_n_destroy(base_node_pointer(_root));
				_head.data = 0;
			}
		}

		explicit
		RedBlackTree( key_compare const& __comp = key_compare(),
			allocator_type const& __alloc = allocator_type() )
		: _head(0), _root(0), _compare(__comp),
			_allocator(__alloc),  _node_allocator()
		{}

		template <class InputIterator>
		RedBlackTree( InputIterator __first, InputIterator __last,
			key_compare const& __comp = key_compare(),
			allocator_type const& __alloc = allocator_type() )
		: _head(0), _root(0), _compare(__comp),
			_allocator(__alloc), _node_allocator()
		{
			_n_range(__first, __last);
		}

		RedBlackTree( RedBlackTree const& __other )
		: _head(0), _root(0), _compare(),
			_allocator(),  _node_allocator()
		{
			_n_range(__other.begin(), __other.end());
		}

		RedBlackTree &
		operator=( RedBlackTree const& __rhs )
		{
			this->clear();
			_n_range(__rhs.begin(), __rhs.end());
			return *this;
		}

		key_compare
		key_comp( void ) const
		{
			return key_compare();
		}

		value_compare
		value_comp( void ) const
		{
			return value_compare();
		}

		/* iterators */

		iterator
		begin( void )
		{
			return iterator(base_node::min(&_head));
		}

		const_iterator
		begin( void ) const
		{
			return const_iterator(base_node::min(&_head));
		}

		iterator
		end( void )
		{
			return iterator(base_node::max(&_head));
		}

		const_iterator
		end( void ) const
		{
			return const_iterator(base_node::max(&_head));
		}

		reverse_iterator
		rbegin( void )
		{
			return reverse_iterator(this->end());
		}

		const_reverse_iterator
		rbegin( void ) const
		{
			return const_reverse_iterator(this->end());
		}

		reverse_iterator
		rend( void )
		{
			return reverse_iterator(this->begin());
		}

		const_reverse_iterator
		rend( void ) const
		{
			return const_reverse_iterator(this->begin());
		}

		/* element acess */

		allocator_type
		get_allocator() const
		{
			return _allocator;
		}

		value_type &
		at( key_type const& __key )
		{
			iterator	n;

			n = _n_find(_root, __key);
			if (n == this->end())
				throw std::out_of_range("RedBlackTree::at");
			return *n;
		}

		value_type const&
		at( key_type const& __key ) const
		{
			const_iterator	n;

			n = _n_find(_root, __key);
			if (n == this->end())
				throw std::out_of_range("RedBlackTree::at");
			return *n;
		}

		/* Capacity */

		bool
		empty( void ) const
		{
			return _head.data == 0;
		}

		size_type
		size( void ) const
		{
			return _head.data;
		}

		size_type
		max_size( void ) const
		{
			return _node_allocator.max_size();
		}

		/* modifiers */

		void
		clear( void )
		{
			if (_head.data)
				_n_destroy(_root);
			_head.left = 0;
			_head.data = 0;
		}

		pair<iterator, bool>
		insert( value_type const& __val )
		{
			return _n_insert(_root, __val);
		}

		iterator
		insert( iterator __position, value_type const& __val )
		{
			return (_n_insert(__position._N_, __val).first);
		}

		template <class InputIterator>
		void
		insert(InputIterator __first, InputIterator __last )
		{
			_n_range(__first, __last);
		}

		void
		erase( iterator __pos )
		{
			if (__pos != this->end())
				_n_erase(__pos._N_, _key_of(*__pos));
		}

		size_type
		erase( key_type const& __key )
		{
			return _n_erase(_root, __key);
		}

		void
		erase(iterator __first, iterator __last)
		{
			iterator tmp;

			while (__first != __last)
			{
				tmp = __first;
				__first++;
				_n_erase(tmp._N_, _key_of(*tmp));
			}
		}

		void
		swap( RedBlackTree & __other )
		{
			std::swap(this->_head.left, __other._head.left);
			if (_root)
				std::swap(this->_root->parent, __other._root->parent);
			std::swap(this->_head.data, __other._head.data);
			std::swap(this->_root, __other._root);
			std::swap(this->_key_of, __other._key_of);
			std::swap(this->_allocator, __other._allocator);
			std::swap(this->_node_allocator, __other._node_allocator);
			std::swap(this->_compare, __other._compare);
		}

		/* operations */

		iterator
		find( key_type const& __key )
		{
			return _n_find(_root, __key);
		}

		const_iterator
		find( key_type const& __key ) const
		{
			return _n_find(_root, __key);
		}

		size_type
		count( key_type const& __key ) const
		{
			try { this->at(__key); }
			catch ( std::out_of_range & ) {
				return false;
			}
			return true;
		}

		iterator
		lower_bound( key_type const& __key )
		{
			base_node_pointer	x = _root;
			base_node_pointer	y = this->end()._N_;

			while (x)
			{
				if (!_compare(_key_of(
						static_cast<node_pointer>(x)->data), __key))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return (iterator(y));
		}

		const_iterator
		lower_bound( key_type const& __key ) const
		{
			base_node_pointer	x = _root;
			base_node_pointer	y = this->end()._N_;

			while (x)
			{
				if (!_compare(_key_of(
					static_cast<node_pointer>(x)->data), __key))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return (const_iterator(y));
		}

		iterator
		upper_bound( key_type const& __key )
		{
			iterator tmp = this->lower_bound(__key);
			if (tmp != this->end())
			{
				if (!_compare(_key_of( static_cast<
						node_pointer>(tmp._N_)->data), __key)
					&& !_compare(__key, _key_of(static_cast<
						node_pointer>(tmp._N_)->data)))
				{
					return ++tmp;
				}
			}
			return tmp;
		}

		const_iterator
		upper_bound( key_type const& __key ) const
		{
			const_iterator tmp = this->lower_bound(__key);
			if (tmp != this->end())
			{
				if (!_compare(_key_of( static_cast<
						node_pointer>(tmp._N_)->data), __key)
					&& !_compare(__key, _key_of(static_cast<
						node_pointer>(tmp._N_)->data)))
				{
					return ++tmp;
				}
			}
			return tmp;
		}

		ft::pair<iterator, iterator>
		equal_range( key_type const& __key )
		{
			return ft::make_pair(this->lower_bound(__key), this->upper_bound(__key));
		}

		ft::pair<const_iterator, const_iterator>
		equal_range( key_type const& __key ) const
		{
			return ft::make_pair(this->lower_bound(__key), this->upper_bound(__key));
		}

		protected:
		/* erase */
		bool
		_n_erase( base_node_pointer __hint, key_type const& __key )
		{
			iterator		pos;
			base_node_pointer	del;
			base_node_pointer	rep;

			if (!_head.data)
				return false;
			pos = _n_find(base_node_pointer(__hint), __key);
			if (pos == this->end())
				return false;
			del = pos._N_;
			rep = _n_erase_sucessor(del);
			/* double black requires tree rebalance */
			if (del->color == black && (!rep || rep->color == black))
				_n_erase_balance(del);
			_n_remove(del);
			/* Bring blackness to root or replacer  */
			if (rep && (rep == _root
				|| (rep->color == red && del->color == black)))
				rep->color = black;
			_n_destroy(del);
			_head.data--;
			return true;
		}

		base_node_pointer
		_n_erase_sucessor( base_node_pointer & __n )
		{
			base_node_pointer	tmp;

			if (!__n)
				return NULL;
			if (__n->left && __n->right)
			{
				tmp = base_node::max(__n->left);
				_allocator.destroy(&static_cast<node_pointer>(__n)->data);
				_allocator.construct(&static_cast<node_pointer>(__n)->data,
						static_cast<node_pointer>(tmp)->data);
				__n = tmp;
				tmp = _n_erase_sucessor(__n);
			}
			if (!__n->left)
				return __n->right;
			if (!__n->right)
				return __n->left;
			return NULL;
		}

		void
		_n_erase_balance( base_node_pointer __d )
		{
			base_node_pointer	s;
			base_node_pointer	i;

			i = __d;
			i->color = double_black;
			/* loop as long as i is not root and i is a double black node, 
				in order to	balance the tree the db node must be removed */
			while (i != _root && i->color == double_black)
			{
				/* the sibling node will be used to decide which "case"
					to call, a sibling is guaranted to exist */
				if (i == i->parent->left)
					s = i->parent->right;
				else
					s = i->parent->left;
				/* if sibling and his children are black, then do a
					"color swap" and repeat as long as parent is also black */
				if (s->color == black && ((!s->left || s->left->color == black)
					&& (!s->right || s->right->color == black)))
				{
					i->color = black;
					s->color = red;
					if (s->parent->color == black)
						s->parent->color = double_black;
					else
						s->parent->color = black;
					i = i->parent;
				}
				/* if sibling is red, swap color with parent and
					rotate db in oposite direction */
				else if (s->color == red)
				{
					std::swap(s->color, s->parent->color);
					if (s == s->parent->right)
						_n_rotate_rr(s, false);
					else
						_n_rotate_ll(s, false);
				}
				else if (i == i->parent->left)
				{
					/* if the near child of s from i is red, 
						swap s color with s near child
						and call the respective rotation */
					if (s->left && s->left->color == red
						&& (!s->right || s->right->color == black))
					{
						std::swap(s->color, s->left->color);
						_n_rotate_ll(s->left, false);
					}
					/* if the far child of s from i is red,
						swap s color with s parent
						and call the respective rotation */
					if (s->right && s->right->color == red)
					{
						std::swap(s->parent->color, s->color);
						_n_rotate_rr(s, false);
						i->color = black;
						s->right->color = black;
						return ;
					}
				}
				/* same as above but for opossite side */
				else 
				{
					if (s->right && s->right->color == red
							&& (!s->left || s->left->color == black))
					{
						std::swap(s->color, s->right->color);
						_n_rotate_rr(s->right, false);
					}
					if (s->left && s->left->color == red)
					{
						std::swap(s->parent->color, s->color);
						_n_rotate_ll(s, false);
						i->color = black;
						s->left->color = black;
						return ;
					}
				}
			}
			_root->color = black;
		}

		/* insert a element incrementing size and balancing the red-black tree
			return a iterator to the inserted element on sucess otherwise end() */
		ft::pair<iterator, bool>
		_n_insert( base_node_pointer __hint, value_type const& __val )
		{
			pair<iterator, bool> tmp;

			if (!_head.data)
			{
				_root = _n_allocate(__val);
				_root->color = black;
				tmp = ft::make_pair(iterator(_root), true);
				_head.left = _root;
				_root->parent = &_head;
			}
			else
			{
				if (!__hint || __hint == this->end()._N_)
					__hint = _root;
				while (__hint != _root && __hint->parent && _compare(_key_of(
					static_cast<node_pointer>(__hint)->data), _key_of(__val)))
				{
					__hint = __hint->parent;
				}
				tmp = _n_insert_find(__hint, __val);
			}
			if (tmp.second)
				_head.data++;
			return tmp;
		}

		/* recursevly find the insert position or duplicated */
		ft::pair<iterator, bool>
		_n_insert_find( base_node_pointer __n, value_type const& __val )
		{
			if (_compare(_key_of(static_cast<
				node_pointer>(__n)->data), _key_of(__val)))
			{
				if (!__n->right)
				{
					__n->right = _n_allocate(__val);
					__n->right->parent = __n;
					__n = __n->right;
					_n_insert_balance(__n);
					return ft::make_pair(iterator(__n), true);
				}
				return (_n_insert_find(__n->right, __val));
			}
			else if (_compare(_key_of(__val),
				_key_of(static_cast<node_pointer>(__n)->data)))
			{
				if (!__n->left)
				{
					__n->left = _n_allocate(__val);
					__n->left->parent = __n;
					__n = __n->left;
					_n_insert_balance(__n);
					return ft::make_pair(iterator(__n), true);
				}
				return (_n_insert_find(__n->left, __val));
			}
			return ft::make_pair(__n, false);
		}

		/* insert_balance performs the required operations to balance */
		void
		_n_insert_balance( base_node_pointer __n )
		{
			/* check for violations as long as parent color is red */
			while (__n != _root
				&& __n->parent->color == red)
			{
				/* if parent is left of grandparent */
				if (__n->parent->parent
					&& __n->parent == __n->parent->parent->left)
				{
					/* if uncle of node is red, apply a color swap */
					if (__n->parent->parent->right
						&& __n->parent->parent->right->color == red)
					{
						_n_insert_cswap(__n, true);
					}
					/* otherwise rotations are require */
					else
					{
						if (__n == __n->parent->right)
							_n_rotate_lr(__n);
						__n = __n->parent;
						__n = _n_rotate_ll(__n, true);
					}
				}
				/* same as above but for oposite side  */
				else if (__n->parent->parent)
				{
					if (__n->parent->parent->left 
						&& __n->parent->parent->left->color == red)
					{
						_n_insert_cswap(__n, false);
					}
					else
					{
						if (__n == __n->parent->left)
							_n_rotate_rl(__n);
						__n = __n->parent;
						__n = _n_rotate_rr(__n, true);
					}
				}
			}
			_root->color = black;
		}

		/* insert_balance helper swaps color with uncle node */
		void
		_n_insert_cswap( base_node_pointer & __n, bool __left_swap )
		{
			__n->parent->color = black;
			__n->parent->parent->color = red;
			if (__left_swap)
				__n->parent->parent->right->color = black;
			else
				__n->parent->parent->left->color = black;
			__n = __n->parent->parent;
		}

		/* red-black tree rotations ( similar to a BST )
			l = left and r = right */

		base_node_pointer
		_n_rotate_ll( base_node_pointer __n, bool __recolor )
		{
			base_node_pointer	tmp;

			tmp = __n->parent;
			tmp->left = __n->right;
			if (tmp->left)
				tmp->left->parent = tmp;
			if (tmp->parent == &_head)
			{
				_root = __n;
				_root->parent = &_head;
				_head.left = _root;
			}
			else if (tmp->parent)
			{
				if (tmp == tmp->parent->left)
					tmp->parent->left = __n;
				else
					tmp->parent->right = __n;
				__n->parent = tmp->parent;
			}
			__n->right = tmp;
			tmp->parent = __n;
			if (__recolor)
			{
				tmp->color = red;
				__n->color = black;
			}
			__n = tmp;
			return __n;
		}

		void
		_n_rotate_lr( base_node_pointer & __n )
		{
			base_node_pointer	tmp;

			tmp = __n;
			__n = __n->parent;
			__n->parent->left = tmp;
			tmp->parent = __n->parent;
			__n->right = tmp->left;
			if (tmp->left)
				tmp->left->parent = __n;
			tmp->left = __n;
			__n->parent = tmp;
		}

		base_node_pointer
		_n_rotate_rr( base_node_pointer __n, bool __recolor )
		{
			base_node_pointer	tmp;

			tmp = __n->parent;
			tmp->right = __n->left;
			if (tmp->right)
				tmp->right->parent = tmp;
			if (tmp->parent == &_head)
			{
				_root = __n;
				_root->parent = &_head;
				_head.left = _root;
			}
			else if (tmp->parent)
			{
				if (tmp == tmp->parent->right)
					tmp->parent->right = __n;
				else
					tmp->parent->left = __n;
				__n->parent = tmp->parent;
			}
			__n->left = tmp;
			tmp->parent = __n;
			if (__recolor)
			{
				tmp->color = red;
				__n->color = black;
			}
			__n = tmp;
			return __n;
		}

		void
		_n_rotate_rl( base_node_pointer & __n )
		{
			base_node_pointer	tmp;

			tmp = __n;
			__n = __n->parent;
			__n->parent->right = tmp;
			tmp->parent = __n->parent;
			__n->left = tmp->right;
			if (tmp->right)
				tmp->right->parent = __n;
			tmp->right = __n;
			__n->parent = tmp;
		}

		/* detach a node and remove it */
		void
		_n_remove( base_node_pointer __n )
		{
			if (!__n)
				return ;
			if (!__n->left)
			{
				if (__n->parent == &_head)
				{
					_root = __n->right;
					if (_root)
						_root->parent = &_head;
					_head.left = _root;
				}
				else
				{
					if (__n == __n->parent->left)
						__n->parent->left = __n->right;
					else
						__n->parent->right = __n->right;
					if (__n->right)
						__n->right->parent = __n->parent;
				}
				__n->right = 0;
			}
			else if (!__n->right)
			{
				if (__n->parent == &_head)
				{
					_root = __n->left;
					if (_root)
						_root->parent = &_head;
					_head.left = _root;
				}
				else
				{
					if (__n == __n->parent->left)
						__n->parent->left = __n->left;
					else
						__n->parent->right = __n->left;
					if (__n->left)
						__n->left->parent = __n->parent;
				}
				__n->left = 0;
			}
		}

		/* allocate a node using the given allocator
			but rebinded to a new type (base_node_pointer) */
		base_node_pointer
		_n_allocate( value_type const& __pair )
		{
			node_pointer tmp = _node_allocator.allocate(1);
			_node_allocator.construct(tmp, __pair);
			return tmp;
		}

		/* destroy a node and all its children */
		void
		_n_destroy( base_node_pointer __n )
		{
			if (!__n)
				return ;
			_n_destroy(__n->left);
			_n_destroy(__n->right);
			_node_allocator.destroy(static_cast<node_pointer>(__n));
			_node_allocator.deallocate(static_cast<node_pointer>(__n), 1);
		}

		/* recursevly search for a key and
			return it on sucess otherwise end() */
		iterator
		_n_find( base_node_pointer __n, key_type const& __key )
		{
			if (!__n)
				return (this->end());
			if (_compare(__key, _key_of(static_cast<node_pointer>(__n)->data)))
				return (_n_find(__n->left, __key));
			else if (_compare(_key_of(static_cast<node_pointer>(__n)->data), __key))
				return (_n_find(__n->right, __key));
			return (iterator(__n));
		}

		const_iterator
		_n_find( base_node_pointer __n, key_type const& __key ) const
		{
			if (!__n)
				return (this->end());
			if (_compare(__key, _key_of(static_cast<node_pointer>(__n)->data)))
				return (_n_find(__n->left, __key));
			else if (_compare(_key_of(static_cast<node_pointer>(__n)->data), __key))
				return (_n_find(__n->right, __key));
			return (const_iterator(__n));
		}

		/* other */

		template <class InputIterator>
		void
		_n_range(InputIterator __first, InputIterator __last)
		{
			while (__first != __last)
			{
				_n_insert(_root, *__first);
				__first++;
			}
		}
	};
}

#endif
