/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:44:46 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/05 11:09:58 by mmosca           ###   ########.fr       */
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

		reverse_iterator() : current() {}
		reverse_iterator(iterator_type x) : current(x) {}
		template<typename U>
		reverse_iterator(const reverse_iterator<U> &other) : current(other.base()) {}
		~reverse_iterator() {}
		template<class U>
		reverse_iterator &operator=(const reverse_iterator<U> &other) {
			this->current = other.current;
			return *this;
		}
		iterator_type base() const {
			return this->current;
		}
		reference operator*() const {
			iterator_type copy(this->current);
			--copy;
			return *copy;
		}
		pointer operator->() const {
			iterator_type copy(this->current);
			--copy;
			return copy.base();
		}
		reference operator[](difference_type n) const {
			return *(this->current.base() - n - 1);
		}
		reverse_iterator<Iter> &operator++() {
			--this->current;
			return *this;
		}
		reverse_iterator<Iter> &operator++(int) {
			iterator_type copy(this->current--);
			return copy;
		}
		reverse_iterator<Iter> &operator--() {
			++this->current;
			return *this;
		}
		reverse_iterator<Iter> &operator--(int) {
			iterator_type copy(this->current++);
			return copy;
		}
		reverse_iterator<Iter> &operator+=(difference_type n) {
			this->current -= n;
			return *this;
		}
		reverse_iterator<Iter> &operator-=(difference_type n) {
			this->current += n;
			return *this;
		}

	protected:
		iterator_type current;
	};

	template<class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
		return lhs.base() == rhs.base();
	}
	template<class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
		return lhs.base() != rhs.base();
	}
	template<class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
		return lhs.base() < rhs.base();
	}
	template<class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
		return lhs.base() <= rhs.base();
	}
	template<class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
		return lhs.base() > rhs.base();
	}
	template<class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
		return lhs.base() >= rhs.base();
	}

	template<class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &it) {
		return it.base() - n;
	}
	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
		return rhs.base() - lhs.base();
	}

}

#endif //FT_CONTAINERS_REVERSE_ITERATOR_HPP
