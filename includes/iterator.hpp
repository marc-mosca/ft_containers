/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:48:32 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/05 12:27:27 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <cstddef>

namespace ft {

	//	~~	ITERATOR_TRAITS ----------------------------------------------------

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

	//	~~	REVERSE_ITERATOR ---------------------------------------------------

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
		reverse_iterator<Iter> operator++(int) {
			iterator_type copy(this->current--);
			return copy;
		}
		reverse_iterator<Iter> &operator--() {
			++this->current;
			return *this;
		}
		reverse_iterator<Iter> operator--(int) {
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

	//	~~	VECTOR_ITERATOR ----------------------------------------------------

	template<class T, class Container>
	class vector_iterator {
	public:
		typedef typename ft::random_access_iterator_tag iterator_category;
		typedef typename iterator_traits<T*>::difference_type difference_type;
		typedef typename iterator_traits<T*>::value_type value_type;
		typedef typename iterator_traits<T*>::pointer pointer;
		typedef typename iterator_traits<T*>::reference reference;

		vector_iterator() : _addr(nullptr) {}
		vector_iterator(T *addr) : _addr(addr) {}
		template<typename U>
		vector_iterator(const vector_iterator<U, Container> &copy) : _addr(copy.base()) {}
		~vector_iterator() {}
		vector_iterator &operator=(const vector_iterator &rhs) {
			this->_addr = rhs._addr;
			return *this;
		}
		pointer base() const {
			return this->_addr;
		}
		reference operator*() const {
			return *this->_addr;
		}
		pointer operator->() const {
			return this->_addr;
		}
		reference operator[](difference_type n) const {
			return *(this->_addr + n);
		}
		vector_iterator &operator++() {
			++this->_addr;
			return *this;
		}
		vector_iterator operator++(int) {
			vector_iterator copy(this->_addr++);
			return copy;
		}
		vector_iterator &operator--() {
			--this->_addr;
			return *this;
		}
		vector_iterator operator--(int) {
			vector_iterator copy(this->_addr--);
			return copy;
		}
		vector_iterator &operator+=(difference_type n) {
			this->_addr += n;
			return *this;
		}
		vector_iterator &operator-=(difference_type n) {
			this->_addr -= n;
			return *this;
		}

	protected:
		pointer _addr;
	};

	template<class T, class Container>
	bool operator==(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
		return lhs.base() == rhs.base();
	}
	template<class T, class Container>
	bool operator!=(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
		return lhs.base() != rhs.base();
	}
	template<class T, class Container>
	bool operator<(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
		return lhs.base() < rhs.base();
	}
	template<class T, class Container>
	bool operator<=(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
		return lhs.base() <= rhs.base();
	}
	template<class T, class Container>
	bool operator>(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
		return lhs.base() > rhs.base();
	}
	template<class T, class Container>
	bool operator>=(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
		return lhs.base() >= rhs.base();
	}

	template<class T, class Container>
	ft::vector_iterator<T, Container> operator+(typename ft::vector_iterator<T, Container>::difference_type n, const ft::vector_iterator<T, Container> &it) {
		return it.base() + n;
	}
	template<class T, class Container>
	typename ft::vector_iterator<T, Container>::difference_type operator-(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
		return rhs.base() - lhs.base();
	}

}

#endif //FT_CONTAINERS_ITERATOR_HPP
