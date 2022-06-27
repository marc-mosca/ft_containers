/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:53:46 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/27 17:14:03 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

	template<class Iter>
	class reverse_iterator
	{
		public:
			//	~~	Member types -----------------------------------------------
			typedef Iter											iterator_type;
			typedef ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef ft::iterator_traits<Iter>::value_type			value_type;
			typedef ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef ft::iterator_traits<Iter>::pointer				pointer;
			typedef ft::iterator_traits<Iter>::reference			reference;

			//	~~	Member functions -------------------------------------------
			reverse_iterator();
			explicit reverse_iterator(iterator_type x);
			template<class U>
			reverse_iterator(const reverse_iterator<U> &other);
			~reverse_iterator();
			template<class U>
			reverse_iterator &operator=(const reverse_iterator<U> &other);
			iterator_type base() const;

		protected:
			//	~~	Member objects ---------------------------------------------
			iterator_type	current;
	};

}

#endif // REVERSE_ITERATOR_HPP
