/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:15:54 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/21 17:17:19 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <vector>

namespace ft
{

	// Don't forget to use ft::vector when it is implemented.
	template < class T, class Container = std::vector<T> >
	class Stack
	{

		public:
			/**
			 *	The first template parameter (T). 
			 */
			typedef T	value_type;

			/**
			 *	The second template parameter (Container).
			 */
			typedef Container	container_type;

			/**
			 *	An unsigned integral type.
			 */
			typedef size_t	size_type;

		public:
			/**
			 * Construct a new stack object
			 * 
			 * @param ctnr container object
			 */
			explicit stack( const container_type& ctnr = container_type() ) : ct(ctnr)
			{
			}

			/**
			 * Returns the number of elements in the stack.
			 * 
			 * @return The number of elements in the underlying container.
			 */
			size_type size() const
			{
				return ( this->ct.size() );
			}

			/**
			 * Returns wheter the stack is empty.
			 * 
			 * @return true if the stack is empty, otherwise, return false
			 */
			bool empty() const
			{
				return ( (this->size() == 0) ? true : false );
			}

		protected:
			container_type	ct;

	};

}

#endif
