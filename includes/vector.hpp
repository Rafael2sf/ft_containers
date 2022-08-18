#pragma once

#include <memory>
#include <assert.h>
#include "vector_iterators.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

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
			typedef vector_iterator<pointer>					iterator;
			typedef vector_iterator<const_pointer>				const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

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
				this->vDestroy();
			}

			explicit vector ( allocator_type const& __alloc = allocator_type() )
			: _data(0), _size(0), _capacity(0), _allocator(__alloc)
			{}

			explicit vector ( size_type __n, value_type const& __val = value_type(),
				allocator_type const& __alloc = allocator_type() )
			: _data(0), _size(0), _capacity(0), _allocator(__alloc)
			{
				this->vFill(__n, __val);
			}

			template <class InputIterator>
			vector ( InputIterator __first, InputIterator __last,
				allocator_type const& __alloc = allocator_type() )
			: _data(0), _size(0), _capacity(0), _allocator(__alloc)
			{
				typedef typename truth_type<is_integral<InputIterator>::value>::type X;
				this->vDispatch(__first, __last, X());
			}

			vector( vector const& __rhs )
			: _data(0), _size(0), _capacity(0), _allocator(allocator_type())
			{
				*this = __rhs;
			}

		/* Operators */

 			vector & operator=( vector const& __rhs )
			{
				if (__rhs._capacity < _capacity)
				{
					this->vErase(this->begin(), this->end());
					for (size_type i = 0; i < __rhs._size; i++)
						_allocator.construct(_data + i, __rhs._data[i]);
					_size = __rhs._size;
				}
				else
				{
					this->vDestroy();
					if (__rhs._size)
					{
						_data = _allocator.allocate(__rhs._capacity);
						for (size_type i = 0; i < __rhs._size; i++)
							_allocator.construct(_data + i, __rhs._data[i]);
						_size = __rhs._size;
						_capacity = __rhs._capacity;
					}
				}
				return *this;
			}

			reference operator[]( size_type __n ) {
				return *(this->_data + __n);
			}

			const_reference operator[]( size_type __n ) const {
				return *(this->_data + __n);
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
				return this->_size == 0;
			}

			void resize( size_type __n, value_type __val = value_type())
			{
				if (__n > max_size())
					throw std::length_error("vector::_M_fill_insert");
				this->vResize(__n);
				for (size_type i = _size; i < __n; i++)
					_allocator.construct(_data + i, __val);
				_size = __n;
			}

			void reserve( size_type __n )
			{
				if (__n > _capacity)
				{
					if (__n > max_size())
						throw std::length_error("vector::reserve");
					this->vResize(__n);
				}
			}

			// Element access

			pointer data( void ) { 
				return _data;
			}

			const pointer data( void ) const {
				return _data;
			}

			reference at( size_type __n ) {
				this->vRangeCheck(__n);
				return _data[__n];
			}

			const_reference	at( size_type __n ) const {
				this->vRangeCheck(__n);
				return _data[__n];
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

			void assign( size_type __n, const_reference __val )
			{
				this->vFill(__n, __val);
			}

			template< class InputIterator >
			void assign( InputIterator __first, InputIterator __last )
			{
				typedef typename truth_type<is_integral<InputIterator>::value>::type X;
				this->vDispatch(__first, __last, X());
			}

			void push_back( const_reference __val )
			{
				if (_size == _capacity)
					this->vResize(_size == 0 ? 1 : _capacity * 2);
				_allocator.construct(_data + _size++, __val);
			}

			void pop_back( void ) {
				_allocator.destroy(_data + --_size);
			}

			iterator insert( iterator __positon, const_reference __val )
			{
				size_type	pos;

				if (_size == _capacity)
				{
					pos = std::distance(this->begin(), __positon);
					this->vResize(_capacity == 0 ? 1 : _capacity * 2);
					__positon = begin() + pos;
				}
				this->vMove(__positon + 1, __positon, std::distance(__positon, this->end()));
				_allocator.construct(&*__positon, __val);
				this->_size++;
				return (__positon);
			}

			void insert( iterator __positon, size_type n, const_reference __val )
			{
				size_type	pos = 0;

				if (_size + n >= _capacity)
				{
					pos = std::distance(this->begin(), __positon);
					this->vResize(_capacity * 2 > _size + n ? _capacity * 2 : _size + n);
					__positon = begin() + pos;
				}
				if (_size)
					this->vMove(__positon + n, __positon, std::distance(__positon, this->end()));
				_size += n;
				while (n--)
					_allocator.construct(&*__positon++, __val);
			}

			template< class InputIterator >
			void insert( iterator __positon, InputIterator __first, InputIterator __last )
			{
				size_type	pos;
				size_type	len;

				len = std::distance(__first, __last);
				if (len == 0)
					return ;
				if (_size + len >= _capacity)
				{
					pos = std::distance(begin(), __positon);
					this->vResize(_capacity * 2 > _size + len ? _capacity * 2 : _size + len);
					__positon = begin() + pos;
				}
				if (_size > 0)
					this->vMove(__positon + len, __positon, std::distance(__positon, this->end()));
				while (__first != __last)
					_allocator.construct(&*__positon++, *__first++);
				_size += len;
			}

			iterator		erase( iterator __positon )
			{
				if (__positon == this->end() - 1)
				{
					_allocator.destroy(&_data[--_size]);
					return (this->end());
				}
				this->vMove(__positon, __positon + 1, std::distance(__positon, this->end()));
				_size--;
				return (__positon == this->end() - 1 ? this->end() : __positon);
			}

			/* Requires iterators */

			iterator		erase( iterator __first, iterator __last )
			{
				size_type	len;
				iterator	tmp;

				len = std::distance(__first, __last);
				if (!len)
					return (__first);
				this->vErase(__first, __last);
				this->vMove(__first, __last, std::distance(__last, this->end()));
				_size -= len;
				return (__last == this->end() - 1 ? this->end() : __last);
			}

			void swap( vector & __other ) {
				std::swap<pointer>(_data, __other._data);
				std::swap<allocator_type>(_allocator, __other._allocator);
				std::swap<size_type>(_size, __other._size);
				std::swap<size_type>(_capacity, __other._capacity);
			}

			void clear( void ) {
				this->vErase(this->begin(), this->end());
				_size = 0;
			}

			iterator begin( void ) {
				return iterator(&_data[0]);
			}

			const_iterator begin( void ) const {
				return const_iterator(&_data[0]);
			}

			iterator end( void ) {
				return iterator(&_data[_size]);
			}

			const_iterator end( void ) const {
				return const_iterator(&_data[_size]);
			}

			reverse_iterator rbegin( void ) {
				return reverse_iterator(&_data[_size]);
			}

			const_reverse_iterator rbegin( void ) const {
				return const_reverse_iterator(&_data[_size]);
			}

			reverse_iterator rend( void ) {
				return reverse_iterator(&_data[0]);
			}

			const_reverse_iterator rend( void ) const {
				return const_reverse_iterator(&_data[0]);
			}

			// Allocator

			allocator_type get_allocator( void ) const {
				return _allocator;
			}

		private:

			void vRangeCheck( size_type __n ) {
				if (__n >= _size)
					throw std::out_of_range("vector::_M_range_check: __n >= this->size()");
			}

			void vMaxCheck( size_type __n ) {
				if (__n > max_size())
					throw std::length_error("cannot create std::vector larger than max_size()");
			}

			/* Resizes the existing memory to a new block, copying the old data,
				will shrink instead if n < size */
			void vResize( size_type __n )
			{
				pointer	tmp;

				if (__n < _size)
				{
					while (--_size > __n)
						_allocator.destroy(_data + _size);
				}
				else if (__n > _capacity)
				{
					this->vMaxCheck(__n);
					tmp = _allocator.allocate(__n);
					if (_size)
						this->vMove(iterator(tmp), this->begin(), _size);
					if (_capacity)
						_allocator.deallocate(_data, _capacity);
					_data = tmp;
					_capacity = __n;
				}
			}

			/* Moves internal data memory from src to __dst of len size,
				dst must be allocated, src is destroyed but not freed */
			void vMove( iterator __dst, iterator __src, size_type __len )
			{
				if (__src == __dst || __len == 0)
					return ;
				if (__dst < __src)
				{
					while (__len--)
					{
						_allocator.construct(&*__dst++, *__src);
						_allocator.destroy(&*__src++);
					}
				}
				else
				{
					__dst += __len - 1;
					__src += __len - 1;
					while (__len--)
					{
						_allocator.construct(&*__dst--, *__src);
						_allocator.destroy(&*__src--);
					}
				}
			}

			template <typename X>
			void	vDispatch( X __n, X __val, true_type )
			{
				this->vFill(static_cast<size_type>(__n), static_cast<value_type>(__val));
			}

			template <typename X>
			void	vDispatch( X __first, X __last, false_type )
			{
				this->vRange(__first , __last);
			}

			/* Destroy the current vector, and create a new vector of n elements with val */
			void vFill( size_type __n, const_reference __val )
			{
				if (_capacity)
					this->vErase(this->begin(), this->end());
				this->vResize(__n);
				for (size_type i = 0; i < __n; i++)
					_allocator.construct(_data + i, __val);
				_size = __n;
			}

			/* Destroy the current vector, and create a vector copy of first-last range */
			template< class InputIterator >
			void vRange( InputIterator __first, InputIterator __last )
			{
				size_t	n;

				if (_capacity)
					this->vErase(this->begin(), this->end());
				n = std::distance(__first, __last);
				this->vResize(n);
				for (size_type i = 0; i < n; i++)
					_allocator.construct(_data + i, *__first++);
				_size = n;
			}

			/* Erase the elements in start->end range without updating _size */
			void vErase( iterator __start, iterator __end )
			{
				if (!_size)
					return ;
				while (__start != __end)
				{
					_allocator.destroy(&*__start);
					__start++;
				}
			}

			/* Destroy and free all the elements and memory inside the vector */
			void vDestroy( void )
			{
				if (_capacity)
				{
					this->vErase(this->begin(), this->end());
					_allocator.deallocate(_data, _capacity);
					_size = 0;
					_capacity = 0;
					_data = 0;
				}
			}
	};

	template <class T, class Alloc>
	bool operator==(vector<T, Alloc> const& __lhs, vector<T, Alloc> const& __rhs)
	{
		if (__lhs.size() != __rhs.size())
			return (false);
		return equal(__lhs.begin(), __lhs.end(), __rhs.begin());
	}

	template <class T, class Alloc>
	bool operator<(vector<T, Alloc> const& __lhs, vector<T, Alloc> const& __rhs)
	{
		return lexicographical_compare(__lhs.begin(), __lhs.end(), __rhs.begin(), __rhs.end());
	}

	template <class T, class Alloc>
	bool operator!=(vector<T, Alloc> const& __lhs, vector<T, Alloc> const& __rhs) {
		return !(__lhs == __rhs);
	}

	template <class T, class Alloc>
	bool operator>(vector<T, Alloc> const& __lhs, vector<T, Alloc> const& __rhs) {
		return __rhs < __lhs;
	}

	template <class T, class Alloc>
	bool operator<=(vector<T, Alloc> const& __lhs, vector<T, Alloc> const& __rhs) {
		return !(__rhs < __lhs);
	}

	template <class T, class Alloc>
	bool operator>=(vector<T, Alloc> const& __lhs, vector<T, Alloc> const& __rhs) {
		return !(__lhs < __rhs);
	}

	template <class T, class Alloc>
	void swap( vector<T,Alloc>& __x, vector<T,Alloc>& __y ) {
		__x.swap(__y);
	}
}
