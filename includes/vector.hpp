#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <cstddef>
#include <cstring>

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

		/* Iterators */

			// typedef MyIterator<value_type>					iterator;
			// typedef MyConstIterator<value_type>				const_iterator;
			// typedef std::reverse_iterator<iterator>			reverse_iterator;
			// typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:

		/* Variables */

			pointer			_p;
			size_type		_size;
			size_type		_block;
			allocator_type	_alloc;

		public:

		/* Constructors */

			~vector()
			{
				this->clear();
			}

			explicit vector ( allocator_type const & alloc = allocator_type() )
			:_p(NULL), _size(0), _block(0), _alloc(alloc)
			{}

			explicit vector ( size_t n, value_type const & val = value_type(),
				allocator_type const & alloc = allocator_type() )
			{}

			template< class InputIterator >
			vector ( InputIterator first, InputIterator last,
				allocator_type const & alloc = allocator_type() )
			{}
			
			/* Vector & problem
 			vector ( ft::vector const & )
			{
				;
			} */

		/* Operators */

			/* vector & problem
 			ft::vector<value_type> &	operator=( ft::vector const & );
			*/
			reference					operator[]( size_type n ) { return (*(this->_p + n)); }
			const_reference				operator[]( size_type n ) const { return (*(this->_p + n)); }

			bool						operator== (const vector<value_type, allocator_type>& rhs);
			bool						operator!= (const vector<value_type, allocator_type>& rhs);
			bool						operator<  (const vector<value_type, allocator_type>& rhs);
			bool						operator<= (const vector<value_type, allocator_type>& rhs);
			bool						operator>  (const vector<value_type, allocator_type>& rhs);
			bool						operator>= (const vector<value_type, allocator_type>& rhs);

		/* Functions */

			// Capacity

			size_type		size( void ) const { return (this->_size); }
			size_type		max_size( void ) const { return (this->_alloc.max_size()); }

			void			resize( size_type n, value_type val = value_type()) ;

			size_type		capacity( void ) const
			{
				return (this->_block);
			}

			bool			empty( void ) const;
			void			reserve( size_type n );

			// Element acess

			reference		at( size_type n );
			const_reference	at( size_type n ) const;
			reference		front( void );
			const_reference	front( void ) const;
			reference		back( void );
			const_reference	back( void ) const;

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
					this->_alloc.deallocate(this->_p, this->_size);
					this->_p = tmp;
					this->_block = new_block;
				}
				this->_alloc.construct(this->_p + this->_size++, val);
			}

			void			pop_back( void );
			/* Requires iterators
			iterator		insert( iterator positon, const_reference val );
			void			insert( iterator positon, size_type n, const_reference val );
			template< class InputIterator >
			void			insert( iterator positon, InputIterator first, InputIterator last );
			iterator		erase( iterator position );
			iterator		erase( iterator first, iterator last );
			*/
			/* Vector & problem
			void			swap( ft::vector & );
			 */

			void			clear( void )
			{
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_p + i);
				this->_alloc.deallocate(this->_p, this->_block);
				this->_block = 0;
				this->_size = 0;
				this->_p = NULL;
			}

			// Allocator

			allocator_type	get_allocator( void ) const { return (Alloc(this->_alloc)); }
	};
}
