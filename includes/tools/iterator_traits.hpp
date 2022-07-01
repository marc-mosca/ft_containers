/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:04:30 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/01 10:59:53 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
	class output_iterator_tag {};
	class input_iterator_tag {};
	class forward_iterator_tag : public input_iterator_tag {};
	class bidirectional_iterator_tag : public forward_iterator_tag {};
	class random_access_iterator_tag : public bidirectional_iterator_tag {};

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

	template<typename Iter>
	typename iterator_traits<Iter>::difference_type	distance(Iter first, Iter last, random_access_iterator_tag)
	{
		return last - first;
	}

	template<typename Iter>
	typename iterator_traits<Iter>::difference_type	distance(Iter first, Iter last, typename iterator_traits<Iter>::iterator_category)
	{
		typename iterator_traits<Iter>::difference_type	dist;

		dist = 0;
		while (first != last)
		{
			first++;
			dist++;
		}
		return dist;
	}

	template<typename Iter>
	typename iterator_traits<Iter>::difference_type	distance(Iter first, Iter last)
	{
		return distance(first, last, typename iterator_traits<Iter>::iterator_category());
	}

	template<class Iter, class Distance>
	void	advance(Iter start, Distance dist, random_access_iterator_tag)
	{
		start += dist;
	}

	template<class Iter, class Distance>
	void	advance(Iter start, Distance dist, typename iterator_traits<Iter>::iterator_category)
	{
		typename iterator_traits<Iter>::difference_type	i;

		i = 0;
		while (i < dist)
		{
			start++;
			i++;
		}
	}

	template<class Iter, class Distance>
	void	advance(Iter start, Distance dist)
	{
		return advance(start, dist, typename iterator_traits<Iter>::iterator_category());
	}
}

#endif // ITERATOR_TRAITS_HPP
