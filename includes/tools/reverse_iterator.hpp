/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:44:46 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/04 17:47:09 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_REVERSE_ITERATOR_HPP
#define FT_CONTAINERS_REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

	template<class Iter>
	class reverse_iterator {
	public:
		typedef Iter iterator_type;
		typedef ft::iterator_traits<Iter>::iterator_category iterator_category;
		typedef ft::iterator_traits<Iter>::value_type value_type;
		typedef ft::iterator_traits<Iter>::difference_type difference_type;
		typedef ft::iterator_traits<Iter>::pointer pointer;
		typedef ft::iterator_traits<Iter>::reference reference;

	protected:
		iterator_type current;
	};

}

#endif //FT_CONTAINERS_REVERSE_ITERATOR_HPP
