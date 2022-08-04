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

			pointer			_data;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_allocator;

		public:

		/* Constructors */

			~vector()
			{
				if (_size)
				{
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_data + i);
					_allocator.deallocate(_data, _capacity);
				}
				_capacity = 0;
				_size = 0;
				//_data = NULL;
			}

			explicit vector ( allocator_type const & alloc = allocator_type() )
			: _size(0), _capacity(0), _allocator(alloc)
			{}

			explicit vector ( size_type n, value_type const & val = value_type(),
				allocator_type const & alloc = allocator_type() )
			: _size(0), _capacity(0), _allocator(alloc)
			{
				if (n > 0)
				{
					vMaxCheck(n);
					_data = _allocator.allocate(n);
					for (size_type i = 0; i < n; i++)
						_allocator.construct(_data + i, val);
				}
				else
					_data = NULL;
				_size = n;
				_capacity = n;
			}

			// template< class InputIterator >
			// vector ( InputIterator first, InputIterator last,
			// 	allocator_type const & alloc = allocator_type() )
			// : _data(NULL), _size(0), _capacity(0), _allocator(alloc)
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
			// 		this->_data = this->_allocator.allocate(n);
			// 		for (size_t i = 0; i < n && first != last; i++, first++)
			// 			this->_allocator.construct(this->_data + i, *first);
			// 	}					if (n > this->max_size())
			// 			throw std::length_error("cannot create std::vector larger than max_size()");
			// 	this->_data = NULL;
			// 	this->_capacity = 0;
			// 	this->_size = 0;
			// }

 			vector( vector const & rhs ) {
				*this = rhs;
			}

		/* Operators */

 			vector & operator=( vector const & ref )
			{
				this->~vector();
				if (ref._size > 0)
				{
					_data = _allocator.allocate(ref._capacity);
					for (size_type i = 0; i < ref._size; i++)
						_allocator.construct(_data + i, ref._data[i]);
					_size = ref._size;
					_capacity = ref._capacity;
				}
				return *this;
			}

			reference operator[]( size_type n ) {
				return *(this->_data + n);
			}

			const_reference operator[]( size_type n ) const {
				return *(this->_data + n);
			}

		/* Functions */

			// Capacity

			size_type size( void ) const {
				return this->_size;
			}

			size_type max_size( void ) const {
				return this->_allocator.max_size();
			}

			size_type capacity( void ) const {
				return this->_capacity;
			}

			bool empty( void ) const {
				return this->_size != 0;
			}

			void resize( size_type n, value_type val = value_type())
			{
				if (n > max_size())
					throw std::length_error("vector::_M_fill_insert");
				vResize(n);
				for (size_type i = _size; i < _capacity; i++)
					_allocator.construct(_data + i, val);
			}

			void reserve( size_type n )
			{
				if (n > _capacity)
				{
					if (n > max_size())
						throw std::length_error("vector::reserve");
					vResize(n);
				}
			}

			// Element acess

			pointer data( void ) { 
				return this->_data;
			}

			const pointer data( void ) const {
				return this->_data;
			}

			reference at( size_type n ) {
				vRangeCheck(n);
				return _data[n];
			}

			const_reference	at( size_type n ) const {
				vRangeCheck(n);
				return _data[n];
			}

			reference front( void ) {
				return *_data;
			}

			const_reference	front( void ) const {
				return *_data;
			}

			reference back( void ) {
				return _data[_size - 1];
			}

			const_reference	back( void ) const {
				return _data[_size - 1];
			}

			// Modifiers

			template< class InputIterator >
			void assign( InputIterator first, InputIterator last );

			void assign( size_type n, const_reference val );
	
			void push_back( const_reference val )
			{
				if (_size == _capacity)
					vResize(_size == 0 ? 1 : _capacity * 2);
				_allocator.construct(_data + _size++, val);
			}

			void pop_back( void ) {
				_allocator.destroy(_data + --_size);
			}

			iterator insert( iterator position, const_reference val )
			{
				size_type	pos;

				if (_size >= _capacity - 1)
				{
					pos = std::distance(begin(), position);
					vResize(_capacity * 2);
					position = begin() + pos;
				}
				vMove(position, position - 1, std::distance(position, end()));
				_allocator.construct(&*position, val);
				this->_size++;
				return (position);
			}

			void insert( iterator position, size_type n, const_reference val )
			{
				size_type	pos;

				if (_size + n >= _capacity)
				{
					pos = std::distance(begin(), position);
					vResize(_capacity * 2 > _size + n ? _capacity * 2 : _size + n);
					position = begin() + pos;
				}
				if (this->_size != 0)
					vMove(position + n - 1, position - 1, std::distance(position, end()));
				_size += n;
				while (n--)
					_allocator.construct(&*position++, val);
			}

			template< class InputIterator>
			void insert( iterator position, InputIterator first, InputIterator last )
			{
				size_type	pos;
				size_type	len;

				len = std::distance(first, last);
				if (len == 0)
					return ;
				vMaxCheck(_size + len);
				if (_size + len >= _capacity)
				{
					pos = std::distance(begin(), position);
					vResize(_capacity * 2 > _size + len ? _capacity * 2 : _size + len);
					position = begin() + pos;
				}
				if (_size > 0)
					vMove(position + len, position, std::distance(position, end()));
				while (first != last)
				{
					std::cout << *first << std::endl;
					_allocator.construct(&*position++, *first++);
				}
				_size += len;
			}

			/* Requires iterators
			iterator		erase( iterator position );
			iterator		erase( iterator first, iterator last );
			*/

			void swap( vector & ref ) {
				std::swap<pointer>(_data, ref._data);
				std::swap<allocator_type>(_allocator, ref._allocator);
				std::swap<size_type>(_size, ref._size);
				std::swap<size_type>(_capacity, ref._capacity);
			}

			void clear( void ) {
				this->~vector();
			}

			iterator begin( void ) {
				return iterator(&_data[0]);
			}
			iterator end( void ) {
				return iterator(&_data[_size]);
			}

			// Allocator

			allocator_type get_allocatorator( void ) const {
				return _allocator;
			}

		protected:

			void vRangeCheck( size_type n ) {
				if (n >= _size)
					throw std::out_of_range("vector::_M_range_check: __n >= this->size()");
			}

			void vMaxCheck( size_type n ) {
				if (n > max_size())
					throw std::length_error("cannot create std::vector larger than max_size()");
			}

			/* Resizes the existing memory to a new block, copying the old data,
				will shrink instead if n < size */
			void vResize( size_type n )
			{
				pointer	tmp;

				if (n < _size)
				{
					while (--_size > n)
					{
						_allocator.destroy(_data + _size);
						*(_data + _size) = 0;
					}
				}
				else if (n != _capacity)
				{
					vMaxCheck(n);
					tmp = _allocator.allocate(n);
					vMove(iterator(tmp), begin(), _size);
					std::cout << "wtf " << *tmp << std::endl;
					if (_capacity)
						_allocator.deallocate(_data, _capacity);
					_data = tmp;
					_capacity = n;
				}
			}

			/* Moves internal data memory from src to dst of len size,
				dst must be allocated, src is destroyed but not freed */
			void vMove( iterator dst, iterator src, size_type len )
			{
				if (src == dst || len == 0)
					return ;
				if (dst < src)
				{
					while (len--)
					{
						_allocator.construct(&*dst++, *src);
						_allocator.destroy(&*src++);
					}
				}
				else
				{
					dst += len;
					src += len;
					while (len--)
					{
						std::cout << "wtf " << *src << std::endl;
						_allocator.construct(&*dst--, *src);
						_allocator.destroy(&*src--);
					}
				}
			}
	};

	// bool						operator== (const vector<value_type, allocator_type>& rhs);
	// bool						operator!= (const vector<value_type, allocator_type>& rhs);
	// bool						operator<  (const vector<value_type, allocator_type>& rhs);
	// bool						operator<= (const vector<value_type, allocator_type>& rhs);
	// bool						operator>  (const vector<value_type, allocator_type>& rhs);
	// bool						operator>= (const vector<value_type, allocator_type>& rhs);
}
