#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "iterators.hpp"
#include "utility.hpp"
#include <stdexcept>
#include <iterator>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

		typedef T
			value_type;
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
		typedef ptrdiff_t
			difference_type;
		typedef ft::random_iterator<value_type>
			iterator;
		typedef ft::random_iterator<const value_type>
			const_iterator;
		typedef ft::reverse_iterator<iterator>
			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>
			const_reverse_iterator;

		/* Variables */

		protected:

		pointer			_data;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;

		public:

		/* Constructors */

		~vector()
		{
			_v_Destroy();
		}

		explicit vector ( allocator_type const& __alloc = allocator_type() )
		: _data(0), _size(0), _capacity(0), _allocator(__alloc)
		{}

		explicit vector ( size_type __n, value_type const& __val = value_type(),
			allocator_type const& __alloc = allocator_type() )
		: _data(0), _size(0), _capacity(0), _allocator(__alloc)
		{
			_v_Fill(__n, __val);
		}

		template <class InputIterator>
		vector ( InputIterator __first, InputIterator __last,
			allocator_type const& __alloc = allocator_type() )
		: _data(0), _size(0), _capacity(0), _allocator(__alloc)
		{
			typedef typename ft::truth_type<
				ft::is_integral<InputIterator>::value>::type X;
			_v_Dispatch(__first, __last, X());
		}

		vector( vector const& __rhs )
		: _data(0), _size(0), _capacity(0), _allocator(allocator_type())
		{
			*this = __rhs;
		}

		/* Operators */

		vector &
		operator=( vector const& __rhs )
		{
			if (_data != __rhs._data)
			{
				if (__rhs._capacity < _capacity)
				{
					_v_Erase(this->begin(), this->end());
					for (size_type i = 0; i < __rhs._size; i++)
						_allocator.construct(_data + i, __rhs._data[i]);
					_size = __rhs._size;
				}
				else
				{
					_v_Destroy();
					if (__rhs._size)
					{
						_data = _allocator.allocate(__rhs._capacity);
						for (size_type i = 0; i < __rhs._size; i++)
							_allocator.construct(_data + i, __rhs._data[i]);
						_size = __rhs._size;
						_capacity = __rhs._capacity;
					}
				}
			}
			return *this;
		}

		reference
		operator[]( size_type __n ) {
			return *(this->_data + __n);
		}

		const_reference
		operator[]( size_type __n ) const {
			return *(this->_data + __n);
		}

		/* Functions */
		// iterators

		iterator
		begin( void ) {
			return iterator(&_data[0]);
		}

		const_iterator
		begin( void ) const {
			return const_iterator(&_data[0]);
		}

		iterator
		end( void ) {
			return iterator(&_data[_size]);
		}

		const_iterator
		end( void ) const {
			return const_iterator(&_data[_size]);
		}

		reverse_iterator
		rbegin( void ) {
			return reverse_iterator(&_data[_size]);
		}

		const_reverse_iterator
		rbegin( void ) const {
			return const_reverse_iterator(&_data[_size]);
		}

		reverse_iterator
		rend( void ) {
			return reverse_iterator(&_data[0]);
		}

		const_reverse_iterator
		rend( void ) const {
			return const_reverse_iterator(&_data[0]);
		}

		// Capacity

		size_type
		size( void ) const {
			return this->_size;
		}

		size_type
		max_size( void ) const {
			return this->_allocator.max_size();
		}

		size_type
		capacity( void ) const {
			return this->_capacity;
		}

		bool
		empty( void ) const {
			return this->_size == 0;
		}

		void
		resize( size_type __n, value_type __val = value_type())
		{
			if (__n > max_size())
				throw std::length_error("vector::_M_fill_insert");
			_v_Resize(__n);
			for (size_type i = _size; i < __n; i++)
				_allocator.construct(_data + i, __val);
			_size = __n;
		}

		void
		reserve( size_type __n )
		{
			if (__n > _capacity)
			{
				if (__n > max_size())
					throw std::length_error("vector::reserve");
				_v_Resize(__n);
			}
		}

		// Element access

		pointer
		data( void ) { 
			return _data;
		}

		const pointer
		data( void ) const {
			return _data;
		}

		reference
		at( size_type __n ) {
			_v_RangeCheck(__n);
			return _data[__n];
		}

		const_reference
		at( size_type __n ) const {
			_v_RangeCheck(__n);
			return _data[__n];
		}

		reference
		front( void ) {
			return *_data;
		}

		const_reference
		front( void ) const {
			return *_data;
		}

		reference
		back( void ) {
			return _data[_size - 1];
		}

		const_reference
		back( void ) const {
			return _data[_size - 1];
		}

		// Modifiers

		void
		assign( size_type __n, const_reference __val )
		{
			_v_Fill(__n, __val);
		}

		template< class InputIterator >
		void
		assign( InputIterator __first, InputIterator __last )
		{
			typedef typename ft::truth_type<
				ft::is_integral<InputIterator>::value>::type X;
			_v_Dispatch(__first, __last, X());
		}

		void
		push_back( const_reference __val )
		{
			if (_size == _capacity)
				_v_Resize(_capacity * 2 + (_capacity == 0));
			_allocator.construct(_data + _size++, __val);
		}

		void
		pop_back( void ) {
			_allocator.destroy(_data + --_size);
		}

		iterator 
		insert( iterator __positon, const_reference __val )
		{
			size_type	pos;

			if (_size == _capacity)
			{
				pos = std::distance(this->begin(), __positon);
				_v_Resize(_capacity * 2 + (_capacity == 0));
				__positon = begin() + pos;
			}
			_v_Move(__positon + 1,
				__positon, std::distance(__positon, this->end()));
			_allocator.construct(&*__positon, __val);
			this->_size++;
			return (__positon);
		}

		void
		insert( iterator __positon, size_type n, const_reference __val )
		{
			size_type	pos = 0;

			if (_size + n > _capacity)
			{
				pos = std::distance(this->begin(), __positon);
				_v_Resize(
					_capacity * 2 > _size + n ? _capacity * 2 : _size + n);
				__positon = begin() + pos;
			}
			if (_size)
				_v_Move(__positon + n,
					__positon, std::distance(__positon, this->end()));
			_size += n;
			while (n--)
				_allocator.construct(&*__positon++, __val);
		}

		template< class InputIterator >
		void
		insert( iterator __position,
			InputIterator __first, InputIterator __last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0 )
		{
			size_type	pos;
			size_type	len;
			ft::pair<pointer, size_type> new_block;
			len = std::distance(__first, __last);
			if (len == 0)
				return ;
			if (_size + len > _capacity)
			{
				pos = std::distance(begin(), __position);
				new_block.second = ( _size + len > _size * 2 ?
					_size + len : _size * 2);
				new_block.first = _allocator.allocate(new_block.second);
				_v_Copy(iterator(new_block.first), this->begin(), pos);
				_v_Copy(iterator(new_block.first + pos), __first, len);
				_v_Copy(iterator(new_block.first + pos + len),
					__position, std::distance(__position, this->end()));
				_v_Erase(begin(), end());
				_allocator.deallocate(_data, _capacity);
				_data = new_block.first;
				_capacity = new_block.second;
			}
			else
			{
				if (_size > 0)
					_v_Move(__position + len,
						__position, std::distance(__position, this->end()));
				_v_Copy(__position, __first, len);
			}
			_size += len;
		}

		iterator
		erase( iterator __positon )
		{
			if (__positon == this->end() - 1)
			{
				_allocator.destroy(&_data[--_size]);
				return (this->end());
			}
			_v_Move(__positon,
				 __positon + 1, std::distance(__positon, this->end()));
			_size--;
			return (__positon == this->end() - 1 ? this->end() : __positon);
		}

		iterator
		erase( iterator __first, iterator __last )
		{
			size_type	len;
			iterator	tmp;

			len = std::distance(__first, __last);
			if (!len)
				return (__first);
			_v_Erase(__first, __last);
			_v_Move(__first, __last, std::distance(__last, this->end()));
			_size -= len;
			return (__last == this->end() - 1 ? this->end() : __last);
		}

		void
		swap( vector & __other ) {
			std::swap<pointer>(_data, __other._data);
			std::swap<allocator_type>(_allocator, __other._allocator);
			std::swap<size_type>(_size, __other._size);
			std::swap<size_type>(_capacity, __other._capacity);
		}

		void
		clear( void ) {
			_v_Erase(this->begin(), this->end());
			_size = 0;
		}


		// Allocator

		allocator_type
		get_allocator( void ) const {
			return allocator_type();
		}

		protected:

		void
		_v_RangeCheck( size_type __n ) const {
			if (__n >= _size)
				throw std::out_of_range(
					"vector::range_check: __n >= this->size()");
		}

		void
		_v_MaxCheck( size_type __n ) const {
			if (__n > max_size())
				throw std::length_error(
					"cannot create std::vector larger than max_size()");
		}

		/* Resizes the existing memory to a new block, copying the old data,
			will shrink instead if n < size */
		void
		_v_Resize( size_type __n )
		{
			pointer	tmp;

			if (__n < _size)
			{
				while (--_size > __n)
					_allocator.destroy(_data + _size);
			}
			else if (__n > _capacity)
			{
				_v_MaxCheck(__n);
				tmp = _allocator.allocate(__n);
				if (_size)
					_v_Move(iterator(tmp), this->begin(), _size);
				if (_capacity)
					_allocator.deallocate(_data, _capacity);
				_data = tmp;
				_capacity = __n;
			}
		}

		/* Moves internal data memory from src to __dst of len size,
			dst must be allocated, src is destroyed but not freed */
		void
		_v_Move( iterator __dst, iterator __src, size_type __len )
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

		/* Moves internal data memory from src to __dst of len size,
			dst must be allocated, src is kept */
		void
		_v_Copy( iterator __dst, iterator __src, size_type __len )
		{
			if (__src == __dst || __len == 0)
				return ;
			while (__len)
			{
				_allocator.construct(&*__dst++, *__src++);
				__len--;
			}
		}

		template <typename X>
		void
		_v_Dispatch( X __n, X __val, true_type )
		{
			_v_Fill(static_cast<size_type>(__n),
				static_cast<value_type>(__val));
		}

		template <typename X>
		void
		_v_Dispatch( X __first, X __last, false_type )
		{
			_v_Range(__first , __last);
		}

		/* Destroy the current vector,
		and create a new vector of n elements with val */
		void
		_v_Fill( size_type __n, const_reference __val )
		{
			if (_capacity)
				_v_Erase(this->begin(), this->end());
			_v_Resize(__n);
			for (size_type i = 0; i < __n; i++)
				_allocator.construct(_data + i, __val);
			_size = __n;
		}

		/* Destroy the current vector,
		and create a vector copy of first-last range */
		template< class InputIterator >
		void
		_v_Range( InputIterator __first, InputIterator __last )
		{
			size_t	n;

			if (__first == this->begin() && __last == this->end())
				return ;
			n = std::distance(__first, __last);
			if (n > _capacity)
			{
				_v_Erase(this->begin(), this->end());
				_size = 0;
				_v_Resize(n);
				_v_Copy(this->begin(), __first, n);
			}
			else
			{
				if (_size >= n)
					_v_Move(this->begin(), __first, n);
				else
				{
					_v_Move(this->begin(), __first, _size);
					std::advance(__first, _size);
					_v_Copy(this->end(), __first, n - _size);
				}
				_v_Erase(this->begin() + n, this->end());
			}
			_size = n;
		}

		/* Erase the elements in start->end range without updating _size */
		void
		_v_Erase( iterator __start, iterator __end )
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
		void
		_v_Destroy( void )
		{
			if (_capacity)
			{
				_v_Erase(this->begin(), this->end());
				_allocator.deallocate(_data, _capacity);
				_size = 0;
				_capacity = 0;
				_data = 0;
			}
		}
	};

	template <class T, class Alloc>
	bool
	operator==( ft::vector<T, Alloc> const& __lhs,
				ft::vector<T, Alloc> const& __rhs )
		{
		if (__lhs.size() != __rhs.size())
			return (false);
		return ft::equal(__lhs.begin(), __lhs.end(), __rhs.begin());
	}

	template <class T, class Alloc>
	bool
	operator<( ft::vector<T, Alloc> const& __lhs,
				ft::vector<T, Alloc> const& __rhs )
		{
		return ft::lexicographical_compare(__lhs.begin(),
			__lhs.end(), __rhs.begin(), __rhs.end());
	}

	template <class T, class Alloc>
	bool
	operator!=( ft::vector<T, Alloc> const& __lhs,
				ft::vector<T, Alloc> const& __rhs )
	{
		return !(__lhs == __rhs);
	}

	template <class T, class Alloc>
	bool
	operator>( ft::vector<T, Alloc> const& __lhs,
				ft::vector<T, Alloc> const& __rhs )
	{
		return __rhs < __lhs;
	}

	template <class T, class Alloc>
	bool
	operator<=( ft::vector<T, Alloc> const& __lhs,
				ft::vector<T, Alloc> const& __rhs )
	{
		return !(__rhs < __lhs);
	}

	template <class T, class Alloc>
	bool
	operator>=( ft::vector<T, Alloc> const& __lhs,
				ft::vector<T, Alloc> const& __rhs )
	{
		return !(__lhs < __rhs);
	}

	template <class T, class Alloc>
	void
	swap( ft::vector<T,Alloc>& __x, ft::vector<T,Alloc>& __y ) {
		__x.swap(__y);
	}
}

#endif
