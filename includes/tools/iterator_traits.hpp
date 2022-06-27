/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:04:30 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/27 19:20:47 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	template<class Iter>
	struct iterator_traits
	{
		typedef Iter::difference_type	difference_type;
		typedef Iter::value_type		value_type;
		typedef Iter::pointer			pointer;
		typedef Iter::reference			reference;
		typedef Iter::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T							*pointer;
		typedef T							&reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef const T						*pointer;
		typedef const T						&reference;
		typedef random_access_iterator_tag	iterator_category;
	};
}

#endif // ITERATOR_TRAITS_HPP
