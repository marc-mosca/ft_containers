/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:04:30 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/27 16:05:35 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
	template<class Iter>
	struct iterator_traits
	{
		typedef Iter::difference_type	difference_type;
		typedef Iter::value_type		value_type;
		typedef Iter::pointer			pointer;
		typedef Iter::reference			reference;
		typedef Iter::iterator_category	iterator_category;
	};
}

#endif // ITERATOR_TRAITS_HPP
