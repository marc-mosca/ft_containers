/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:16:48 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/04 17:29:18 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ITERATOR_TRAITS_HPP
#define FT_CONTAINERS_ITERATOR_TRAITS_HPP

#include <cstddef>

namespace ft {

	class output_iterator_tag {};
	class input_iterator_tag {};
	class forward_iterator_tag : public input_iterator_tag {};
	class bidirectional_iterator_tag : public forward_iterator_tag {};
	class random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template<class Iter>
	struct iterator_traits {
		typedef Iter::iterator_category iterator_category;
		typedef Iter::value_type value_type;
		typedef Iter::difference_type difference_type;
		typedef Iter::pointer pointer;
		typedef Iter::reference reference;
	};

	template<class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T *pointer;
		typedef T &reference;
	};

	template<class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const T *pointer;
		typedef const T &reference;
	};

	template<typename Iter>
	typename iterator_traits<Iter>::difference_type distance(Iter first, Iter last, random_access_iterator_tag) {
		return last - first;
	}

	template<typename Iter>
	typename iterator_traits<Iter>::difference_type distance(Iter first, Iter last, typename iterator_traits<Iter>::iterator_category) {
		typename iterator_traits<Iter>::difference_type dist = 0;
		for (; first != last; ++first, ++dist)
			;
		return dist;
	}

	template<typename Iter>
	typename iterator_traits<Iter>::difference_type distance(Iter first, Iter last) {
		return distance(first, last, typename iterator_traits<Iter>::iterator_category());
	}

	template<class Iter, class Distance>
	void advance(Iter start, Distance dist, random_access_iterator_tag) {
		start += dist;
	}

	template<class Iter, class Distance>
	void advance(Iter start, Distance dist, typename iterator_traits<Iter>::iterator_category) {
		for (typename iterator_traits<Iter>::iterator_category i = 0; i < dist; ++i, ++start)
			;
	}

	template<class Iter, class Distance>
	void advance(Iter start, Distance dist) {
		advance(start, dist, typename iterator_traits<Iter>::iterator_category());
	}

}

#endif //FT_CONTAINERS_ITERATOR_TRAITS_HPP
