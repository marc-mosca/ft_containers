/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:15:54 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/22 16:22:37 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <vector>

namespace ft
{

	template < class T, class Container = std::vector<T> >
	class Stack
	{

		public:
			/**
			 *	The first template parameter (T). 
			 */
			typedef Container::value_type		value_type;

			/**
			 *	The second template parameter (Container).
			 */
			typedef Container					container_type;

			/**
			 *	An unsigned integral type.
			 */
			typedef Container::size_type		size_type;

			/**
			 * A reference to value_type.
			 */
			typedef Container::reference		reference;
			
			/**
			 * A const reference to value_type.
			 */
			typedef Container::const_reference	const_reference;

		public:
			/**
			 * Constructs a stack container adaptor object.
			 * 
			 * @param ctnr container object
			 */
			explicit stack( const container_type& ctnr = container_type() )
				: c(ctnr)
			{
			}

			/**
			 * Destroy the stack object.
			 */
			~stack()
			{
			}

			/**
			 * Check if the stack is empty or not.
			 * 
			 * @return if the stack is empty, returns true, otherwise return false
			 */
			bool empty() const
			{
				return ( (this->size() == 0) ? true : false );
			}

			/**
			 * Computes the number of elements in the stack container.
			 * 
			 * @return the number of elements in the underlying container
			 */
			size_type size() const
			{
				return ( this->c.size() );
			}

			/**
			 * Search and return a reference to the last element in the
			 * container.
			 * 
			 * @return a reference to the last element in the container
			 */
			reference top()
			{
				return ( this->c.back() );
			}

			/**
			 * Search and return a const reference to the last element in the
			 * container.
			 * 
			 * @return a const reference to the last element in the container
			 */
			const_reference top() const
			{
				return ( this->c.back() );
			}

			/**
			 * Inserts a new element at the top of the stack. The content of
			 * this new element is initialized to a copy of val.
			 * 
			 * @param val value to which the inserted element is initialized
			 */
			void push( const_reference val )
			{
				this->c.push_back(val);
			}

			/**
			 * Removes the top element from the stack.
			 */
			void pop()
			{
				this->c.pop_back();
			}

			template < class Tx, class Containerx >
			friend bool operator==( const ft::stack< Tx, Containerx >& lhs, const ft::stack< Tx, Containerx >& rhs )
			{
				return ( lhs.c == rhs.c );
			}

		protected:
			/**
			 * the underlying container.
			 */
			container_type	c;

	};

}

#endif
