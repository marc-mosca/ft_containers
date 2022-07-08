/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:39:57 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/08 14:57:04 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <cstddef>

namespace ft {

	/**
	 * Defines the category of an iterator. Each tag is an empty type.
	 */
	class output_iterator_tag {};
	class input_iterator_tag {};
	class forward_iterator_tag : public input_iterator_tag {};
	class bidirectional_iterator_tag : public forward_iterator_tag {};
	class random_access_iterator_tag : public bidirectional_iterator_tag {};

	/**
	 * ft::iterator is the base class provided to simplify definitions of the required types for iterators.
	 * @tparam Category the category of the iterator, must be one of iterator category tags
	 * @tparam T the type of the values that can be obtained by dereferencing the iterator, this type should be void for output iterators
	 * @tparam Distance a type that can be used to identify distance between iterators
	 * @tparam Pointer defines a pointer to the type iterated over (T)
	 * @tparam Reference defines a reference to the type iterated over (T)
	 */
	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		/**
		 * Member types
		 */
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	/**
	 * ft::iterator_traits is the type trait class that provides uniform interface to the properties of LegacyIterator types.
	 * @tparam Iter the iterator type to retrieve properties for
	 */
	template<class Iter>
	struct iterator_traits {
		/**
		 * Member types
		 */
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T*> {
		/**
		 * Member types
		 */
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*> {
		/**
		 * Member types
		 */
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};

	/**
	 * Returns the number of hops from first to last.
	 * @tparam InputIt must meet the requirements of LegacyInputIterator
	 * @param first iterator pointing to the first element
	 * @param last iterator pointing to the end of the range
	 * @return the number of increments needed to go from first to last
	 */
	template<class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last, ft::random_access_iterator_tag) {
		return last - first;
	}

	/**
	 * Returns the number of hops from first to last.
	 * @tparam InputIt must meet the requirements of LegacyInputIterator
	 * @param first iterator pointing to the first element
	 * @param last iterator pointing to the end of the range
	 * @return the number of increments needed to go from first to last
	 */
	template<class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last, typename ft::iterator_traits<InputIt>::iterator_category) {
		typename ft::iterator_traits<InputIt>::difference_type result = 0;
		while (first != last) {
			++first;
			++result;
		}
		return result;
	}

	/**
	 * Returns the number of hops from first to last.
	 * @tparam InputIt must meet the requirements of LegacyInputIterator
	 * @param first iterator pointing to the first element
	 * @param last iterator pointing to the end of the range
	 * @return the number of increments needed to go from first to last
	 */
	template<typename InputIt>
	typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last) {
		return distance(first, last, typename ft::iterator_traits<InputIt>::iterator_category());
	}

	/**
	 * Increments given iterator it by n elements.
	 * @tparam InputIt must meet the requirements of LegacyInputIterator
	 * @param it iterator to be advanced
	 * @param n number of elements it should be advanced
	 */
	template<class InputIt>
	void advance(InputIt &it, typename ft::iterator_traits<InputIt>::difference_type n, ft::input_iterator_tag) {
		while (n > 0) {
			--n;
			++it;
		}
	}

	/**
	 * Increments given iterator it by n elements.
	 * @tparam InputIt must meet the requirements of LegacyInputIterator
	 * @param it iterator to be advanced
	 * @param n number of elements it should be advanced
	 */
	template<class InputIt>
	void advance(InputIt &it, typename ft::iterator_traits<InputIt>::difference_type n, ft::bidirectional_iterator_tag) {
		while (n > 0) {
			--n;
			++it;
		}
		while (n < 0) {
			++n;
			--it;
		}
	}

	/**
	 * Increments given iterator it by n elements.
	 * @tparam InputIt must meet the requirements of LegacyInputIterator
	 * @param it iterator to be advanced
	 * @param n number of elements it should be advanced
	 */
	template<class InputIt>
	void advance(InputIt &it, typename ft::iterator_traits<InputIt>::difference_type n, ft::random_access_iterator_tag) {
		it += n;
	}

	/**
	 * Increments given iterator it by n elements.
	 * @tparam InputIt must meet the requirements of LegacyInputIterator
	 * @param it iterator to be advanced
	 * @param n number of elements it should be advanced
	 */
	template<class InputIt, class Distance>
	void advance(InputIt &it, Distance n) {
		ft::advance(it, typename ft::iterator_traits<InputIt>::difference_type(n), typename ft::iterator_traits<InputIt>::iterator_category());
	}

	/**
	 * ft::reverse_iterator is an iterator adaptor that reverses the direction of a given iterator, which must be at least a LegacyBidirectionalIterator.
	 */
	template<class Iter>
	class reverse_iterator {
	public:
		/**
		 * Member types
		 */
		typedef Iter iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer pointer;
		typedef typename ft::iterator_traits<Iter>::reference reference;

		/**
		 * Default constructor. The underlying iterator is value-initialized.
		 */
		reverse_iterator() : current() {}

		/**
		 * The underlying iterator is initialized with x.
		 * @param x iterator to adapt
		 */
		reverse_iterator(iterator_type x) : current(x) {}

		/**
		 * The underlying iterator is initialized with that of other.
		 * @param other iterator adaptor to copy
		 */
		template<typename U>
		reverse_iterator(const ft::reverse_iterator<U> &other) : current(other.base()) {}

		/**
		 * Destructor.
		 */
		~reverse_iterator() {}

		/**
		 * The underlying iterator is assigned the value of the underlying iterator of other.
		 * @param other iterator adaptor to assign
		 * @return *this
		 */
		template<class U>
		ft::reverse_iterator<Iter> &operator=(const ft::reverse_iterator<U> &other) {
			this->current = other.base();
			return *this;
		}

		/**
		 * Returns the underlying base iterator.
		 * @return the underlying iterator
		 */
		iterator_type base() const {
			return this->current;
		}

		/**
		 * Returns a reference to the element previous to current.
		 * @return reference to the element previous to current
		 */
		reference operator*() const {
			iterator_type tmp = this->base();
			return *--tmp;
		}

		/**
		 * Returns a pointer to the element previous to current.
		 * @return pointer to the element previous to current
		 */
		pointer operator->() const {
			iterator_type tmp = this->base();
			--tmp;
			return tmp.base();
		}

		/**
		 * Returns a reference to the element at specified relative location.
		 * @param n position relative to current location
		 * @return a reference to the element at relative location, that is, base()[-n-1]
		 */
		reference operator[](difference_type n) const {
			return *(this->current.base() - n - 1);
		}

		/**
		 * Pre-increments by one respectively.
		 * @return *this
		 */
		ft::reverse_iterator<Iter> &operator++() {
			--this->current;
			return *this;
		}

		/**
		 * Post-increments by one respectively.
		 * @return a copy of *this that was made before the change
		 */
		ft::reverse_iterator<Iter> &operator++(int) {
			iterator_type tmp = this->current--;
			return tmp;
		}

		/**
		 * Pre-decrements by one respectively.
		 * @return *this
		 */
		ft::reverse_iterator<Iter> &operator--() {
			++this->current;
			return *this;
		}

		/**
		 * Post-decrements by one respectively.
		 * @return a copy of *this that was made before the change
		 */
		ft::reverse_iterator<Iter> &operator--(int) {
			iterator_type tmp = this->current++;
			return tmp;
		}

		/**
		 * Returns an iterator which is advanced by n positions respectively.
		 * @param n position relative to current location
		 * @return reverse_iterator(base()-n)
		 */
		ft::reverse_iterator<Iter> &operator+(difference_type n) {
			return this->base() - n;
		}

		/**
		 * Returns an iterator which is advanced by -n positions respectively.
		 * @param n position relative to current location
		 * @return reverse_iterator(base()+n)
		 */
		ft::reverse_iterator<Iter> &operator-(difference_type n) {
			return this->base() + n;
		}

		/**
		 * Advances the iterator by n positions respectively.
		 * @param n position relative to current location
		 * @return *this
		 */
		ft::reverse_iterator<Iter> &operator+=(difference_type n) {
			this->current += n;
			return *this;
		}

		/**
		 * Advances the iterator by -n positions respectively.
		 * @param n position relative to current location
		 * @return *this
		 */
		ft::reverse_iterator<Iter> &operator-=(difference_type n) {
			this->current -= n;
			return *this;
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Iterator1, class Iterator2>
		friend bool operator==(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
			return lhs.base() == rhs.base();
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Iterator1, class Iterator2>
		friend bool operator!=(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
			return lhs.base() != rhs.base();
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Iterator1, class Iterator2>
		friend bool operator>(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
			return lhs.base() > rhs.base();
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Iterator1, class Iterator2>
		friend bool operator>=(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
			return lhs.base() >= rhs.base();
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Iterator1, class Iterator2>
		friend bool operator<(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
			return lhs.base() < rhs.base();
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Iterator1, class Iterator2>
		friend bool operator<=(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs) {
			return lhs.base() <= rhs.base();
		}

	protected:
		/**
		 * Member objects
		 */
		iterator_type current;
	};

	template<class T, class Container>
	class vector_iterator {
	public:
		/**
		 * Member types
		 */
		typedef typename ft::random_access_iterator_tag iterator_category;
		typedef typename ft::iterator_traits<T*>::difference_type difference_type;
		typedef typename ft::iterator_traits<T*>::value_type value_type;
		typedef typename ft::iterator_traits<T*>::pointer pointer;
		typedef typename ft::iterator_traits<T*>::reference reference;

		/**
		 * Default constructor.
		 */
		vector_iterator() : _addr(nullptr) {}

		/**
		 * Constructor with initialized _addr with a pointer to T.
		 * @param addr pointer to set
		 */
		vector_iterator(pointer addr) : _addr(addr) {}

		/**
		 * Vector iterator is initialized with that of copy.
		 * @param copy vector_iterator to copy
		 */
		template<typename U>
		vector_iterator(const vector_iterator<U, Container> &copy) : _addr(copy.base()) {}

		/**
		 * Destructor.
		 */
		~vector_iterator() {}

		/**
		 * The underlying iterator is assigned the value of the underlying iterator of other.
		 * @param other iterator adaptor to assign
		 * @return *this
		 */
		ft::vector_iterator<T, Container> &operator=(const ft::vector_iterator<T, Container> &other) {
			this->_addr = other.base();
			return *this;
		}

		/**
		 * Returns the underlying base iterator.
		 * @return the underlying iterator
		 */
		pointer base() const {
			return this->_addr;
		}

		/**
		 * Returns a reference to the element previous to current.
		 * @return reference to the element previous to current
		 */
		reference operator*() const {
			pointer tmp = this->base();
			return *--tmp;
		}

		/**
		 * Returns a pointer to the element previous to current.
		 * @return pointer to the element previous to current
		 */
		pointer operator->() const {
			pointer tmp = this->base();
			--tmp;
			return tmp.base();
		}

		/**
		 * Returns a reference to the element at specified relative location.
		 * @param n position relative to current location
		 * @return a reference to the element at relative location, that is, base()[-n-1]
		 */
		reference operator[](difference_type n) const {
			return *(this->current.base() - n - 1);
		}

		/**
		 * Pre-increments by one respectively.
		 * @return *this
		 */
		ft::vector_iterator<T, Container> &operator++() {
			--this->current;
			return *this;
		}

		/**
		 * Post-increments by one respectively.
		 * @return a copy of *this that was made before the change
		 */
		ft::vector_iterator<T, Container> &operator++(int) {
			ft::vector_iterator<T, Container> tmp = this->current--;
			return tmp;
		}

		/**
		 * Pre-decrements by one respectively.
		 * @return *this
		 */
		ft::vector_iterator<T, Container> &operator--() {
			++this->current;
			return *this;
		}

		/**
		 * Post-decrements by one respectively.
		 * @return a copy of *this that was made before the change
		 */
		ft::vector_iterator<T, Container> &operator--(int) {
			ft::vector_iterator<T, Container> tmp = this->current++;
			return tmp;
		}

		/**
		 * Returns an iterator which is advanced by n positions respectively.
		 * @param n position relative to current location
		 * @return reverse_iterator(base()-n)
		 */
		ft::vector_iterator<T, Container> &operator+(difference_type n) {
			return this->base() - n;
		}

		/**
		 * Returns an iterator which is advanced by -n positions respectively.
		 * @param n position relative to current location
		 * @return reverse_iterator(base()+n)
		 */
		ft::vector_iterator<T, Container> &operator-(difference_type n) {
			return this->base() + n;
		}

		/**
		 * Advances the iterator by n positions respectively.
		 * @param n position relative to current location
		 * @return *this
		 */
		ft::vector_iterator<T, Container> &operator+=(difference_type n) {
			this->current += n;
			return *this;
		}

		/**
		 * Advances the iterator by -n positions respectively.
		 * @param n position relative to current location
		 * @return *this
		 */
		ft::vector_iterator<T, Container> &operator-=(difference_type n) {
			this->current -= n;
			return *this;
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		friend bool operator==(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
			return lhs.base() == rhs.base();
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		friend bool operator!=(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
			return lhs.base() != rhs.base();
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		friend bool operator>(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
			return lhs.base() > rhs.base();
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		friend bool operator>=(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
			return lhs.base() >= rhs.base();
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Iterator1, class Iterator2>
		friend bool operator<(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
			return lhs.base() < rhs.base();
		}

		/**
		 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
		 * @param lhs iterator adaptors to compare
		 * @param rhs iterator adaptors to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		friend bool operator<=(const ft::vector_iterator<T, Container> &lhs, const ft::vector_iterator<T, Container> &rhs) {
			return lhs.base() <= rhs.base();
		}

	protected:
		pointer _addr;
	};

}

#endif //FT_CONTAINERS_ITERATOR_HPP
