#pragma once

#include <memory>
#include <vector>
#include <cstddef>
#include <algorithm>

#include "vector_iterators.hpp"
#include "type_traits.hpp"
#include <iostream>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

		/* Member types */

			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef size_t										size_type;
			typedef ptrdiff_t									difference_type;
			typedef vector_iterator<value_type>					iterator;
		// typedef ft::vector_const_iterator<value_type>		const_iterator;
		// typedef std::reverse_iterator<iterator>				reverse_iterator;
		// typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

		/* Variables */

		private:

			pointer			_p;
			size_type		_size;
			size_type		_block;
			allocator_type	_alloc;

		public:

		/* Constructors */

			~vector()
			{
				if (this->_size)
				{
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_p + i);
					this->_alloc.deallocate(this->_p, this->_block);
				}
				this->_block = 0;
				this->_size = 0;
				this->_p = NULL;
			}

			explicit vector ( allocator_type const & alloc = allocator_type() )
			:_p(NULL), _size(0), _block(0), _alloc(alloc)
			{}

			explicit vector ( size_type n, value_type const & val = value_type(),
				allocator_type const & alloc = allocator_type() )
			: _alloc(alloc)
			{
				std::cout << "HERE\n";
				if (n > this->max_size())
					throw std::length_error("cannot create std::vector larger than max_size()");
				if (n > 0)
				{
					this->_p = this->_alloc.allocate(n);
					for (size_type i = 0; i < n; i++)
						this->_alloc.construct(this->_p + i, val);
				}
				else
					this->_p = NULL;
				this->_size = n;
				this->_block = n;
			}

			// template< class InputIterator >
			// vector ( InputIterator first, InputIterator last,
			// 	allocator_type const & alloc = allocator_type() )
			// :_p(NULL), _size(0), _block(0), _alloc(alloc)
			// {
			// 	size_type	n;

			// 	std::cout << "in constructor" << std::endl;
			// 	if (ft::is_integral<InputIterator>::value)
			// 	{
			// 		*this = vector<T>(static_cast<size_type>(first), last);
			// 		return ;
			// 	}
			// 	else
			// 	{
			// 		n = std::distance(first ,last);
			// 		if (n > this->max_size())
			// 			throw std::length_error("cannot create std::vector larger than max_size()");
			// 		this->_p = this->_alloc.allocate(n);
			// 		for (size_t i = 0; i < n && first != last; i++, first++)
			// 			this->_alloc.construct(this->_p + i, *first);
			// 	}					if (n > this->max_size())
			// 			throw std::length_error("cannot create std::vector larger than max_size()");
			// 	this->_p = NULL;
			// 	this->_block = 0;
			// 	this->_size = 0;
			// }

 			vector( vector const & rhs )
			{
				*this = rhs;
			}

		/* Operators */

 			vector &	operator=( vector const & ref )
			{
				this->_p = NULL;
				this->_size = 0;
				this->_block = 0;
				if (ref._size > 0)
				{
					this->_p = this->_alloc.allocate(ref._size);
					for (size_type i = 0; i < ref._size; i++)
						this->_alloc.construct(this->_p + i, ref._p[i]);
					this->_size = ref._size;
					this->_block = ref._block;
				}
				return (*this);
			}

			reference		operator[]( size_type n ) { return (*(this->_p + n)); }
			const_reference	operator[]( size_type n ) const { return (*(this->_p + n)); }

		/* Functions */

			// Capacity

			size_type		size( void ) const { return (this->_size); }
			size_type		max_size( void ) const { return (this->_alloc.max_size()); }
			size_type		capacity( void ) const { return (this->_block); }
			bool			empty( void ) const { return (this->_size != 0); }
			void			resize( size_type n, value_type val = value_type())
			{
				pointer	tmp;

				if (n > this->max_size())
					throw std::length_error("vector::_M_fill_insert");
				if (n < this->_size)
				{
					while (--this->_size > n)
					{
						this->_alloc.destroy(this->_p + this->_size);
						*(this->_p + this->_size) = 0;
					}
					this->_alloc.destroy(this->_p + this->_size);
					*(this->_p + this->_size) = 0;
				}
				else
				{
					tmp = this->_alloc.allocate(n);
					for (size_type i = 0; i < this->_size; i++)
					{
						this->_alloc.construct(tmp + i, this->_p[i]);
						this->_alloc.destroy(this->_p + i);
					}
					for (size_type i = this->_size; i < n; i++)
						this->_alloc.construct(tmp + i, val);
					this->_alloc.deallocate(this->_p, this->_block);
					this->_p = tmp;
					this->_size = n;
				}
			}

			void			reserve( size_type n )
			{
				pointer	tmp;

				if (n > this->_block)
				{
					if (n > this->max_size())
						throw std::length_error("vector::reserve");
					tmp = this->_alloc.allocate(n);
					for (size_type i = 0; i < this->_size; i++)
					{
						this->_alloc.construct(tmp + i, this->_p[i]);
						this->_alloc.destroy(this->_p + i);
					}
					this->_alloc.deallocate(this->_p, this->_block);
					this->_p = tmp;
					this->_block = n;
				}
			}

			// Element acess

			pointer			data( void ) { return this->_p; }
			const pointer	data( void ) const { return this->_p; }
			reference		at( size_type n ) {
				this->_range_check(n);
				return (this->_p[n]);
			}
			const_reference	at( size_type n ) const {
				this->_range_check(n);
				return (this->_p[n]);
			}
			reference		front( void ){ return (*this->_p); }
			const_reference	front( void ) const { return (*this->_p); }
			reference		back( void ) { return (this->_p[this->_size - 1]); }
			const_reference	back( void ) const { return (this->_p[this->_size - 1]); }

			// Modifiers

			template< class InputIterator >
			void			assign( InputIterator first, InputIterator last );
			void			assign( size_type n, const_reference val );
			void			push_back( const_reference val )
			{
				pointer		tmp;
				size_type	new_block;

				if (this->_size == this->_block)
				{
					this->_size == 0 ? new_block = 1 : new_block = this->_block * 2;
					tmp = this->_alloc.allocate(new_block);
					for (size_type i = 0; i < this->_size; i++)
					{
						this->_alloc.construct(tmp + i, this->_p[i]);
						this->_alloc.destroy(this->_p + i);
					}
					this->_alloc.deallocate(this->_p, this->_block);
					this->_p = tmp;
					this->_block = new_block;
				}
				this->_alloc.construct(this->_p + this->_size++, val);
			}
			void			pop_back( void ) { this->_alloc.destroy(this->_p + --this->_size); }

			iterator		insert( iterator position, const_reference val )
			{
				iterator	it = this->begin();
				pointer		tmp;
				size_type	i;
				size_type	new_block;

				if (this->_size == 0 || position >= this->end())
				{
					this->push_back(val);
					position = this->end() - 1;
				}
				else
				{
					new_block = this->_block;
					if (this->_size == 0)
						new_block = 1;
					else if (this->_size == this->_block)
						new_block = this->_block * 2;
					
					if (new_block == this->_block)
					{
						T tmp, curr;

						i = std::distance(this->begin(), position);
						tmp = this->_p[i];
						this->_alloc.destroy(this->_p + i);
						this->_alloc.construct(this->_p + i, val);
						while (++i < this->_size)
						{
							curr = this->_p[i];
							this->_alloc.destroy(this->_p + i);
							this->_alloc.construct(this->_p + i, tmp);
							tmp = curr;
						}
					}
					else
					{
						i = 0;
						tmp = this->_alloc.allocate(new_block);
						while (it != position)
						{
							this->_alloc.construct(tmp + i, *it++);
							this->_alloc.destroy(this->_p + i++);
						}
						position = iterator(&tmp[i]);
						this->_alloc.construct(tmp + i++, val);
						while (it < this->end())
						{
							this->_alloc.construct(tmp + i, *it++);
							this->_alloc.destroy(this->_p + i++ - 1);
						}
						this->_alloc.deallocate(this->_p, this->_block);
						this->_p = tmp;
						this->_block = new_block;
					}
					this->_size += 1;
				}
				return (position);
			}

			/* Requires iterators
			void			insert( iterator positon, size_type n, const_reference val );
			template< class InputIterator >
			void			insert( iterator positon, InputIterator first, InputIterator last );
			iterator		erase( iterator position );
			iterator		erase( iterator first, iterator last );
			*/

			void			swap( vector & ref ) {
				std::swap<pointer>(this->_p, ref._p);
				std::swap<allocator_type>(this->_alloc, ref._alloc);
				std::swap<size_type>(this->_size, ref._size);
				std::swap<size_type>(this->_block, ref._block);
			}

			void			clear( void ) { this->~vector(); }

			iterator begin( void ) {
				return iterator(&this->_p[0]);
			}
			iterator end( void ) {
				return iterator(&this->_p[this->_size]);
			}

			// Allocator

			allocator_type	get_allocator( void ) const { return (Alloc(this->_alloc)); }

		protected:

			void	_range_check(size_type n) {
				if (n >= this->_size)
					throw std::out_of_range("vector::_M_range_check: __n >= this->size()");
			}
	};

	// bool						operator== (const vector<value_type, allocator_type>& rhs);
	// bool						operator!= (const vector<value_type, allocator_type>& rhs);
	// bool						operator<  (const vector<value_type, allocator_type>& rhs);
	// bool						operator<= (const vector<value_type, allocator_type>& rhs);
	// bool						operator>  (const vector<value_type, allocator_type>& rhs);
	// bool						operator>= (const vector<value_type, allocator_type>& rhs);
}
