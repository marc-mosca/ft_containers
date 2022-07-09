/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:39:57 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/09 20:17:56 by mmosca           ###   ########.fr       */
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
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
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
			current = other.base();
			return *this;
		}

		/**
		 * Returns the underlying base iterator.
		 * @return the underlying iterator
		 */
		iterator_type base() const {
			return current;
		}

		/**
		 * Returns a reference to the element previous to current.
		 * @return reference to the element previous to current
		 */
		reference operator*() const {
			iterator_type tmp(current);
			--tmp;
			return *tmp;
		}

		/**
		 * Returns a pointer to the element previous to current.
		 * @return pointer to the element previous to current
		 */
		pointer operator->() const {
			iterator_type tmp(current);
			--tmp;
			return tmp.base();
		}

		/**
		 * Returns a reference to the element at specified relative location.
		 * @param n position relative to current location
		 * @return a reference to the element at relative location, that is, base()[-n-1]
		 */
		reference operator[](difference_type n) const {
			return *(current.base() - n - 1);
		}

		/**
		 * Pre-increments by one respectively.
		 * @return *this
		 */
		ft::reverse_iterator<Iter> &operator++() {
			--current;
			return *this;
		}

		/**
		 * Post-increments by one respectively.
		 * @return a copy of *this that was made before the change
		 */
		ft::reverse_iterator<Iter> operator++(int) {
			iterator_type tmp(current--);
			return tmp;
		}

		/**
		 * Pre-decrements by one respectively.
		 * @return *this
		 */
		ft::reverse_iterator<Iter> &operator--() {
			++current;
			return *this;
		}

		/**
		 * Post-decrements by one respectively.
		 * @return a copy of *this that was made before the change
		 */
		ft::reverse_iterator<Iter> operator--(int) {
			iterator_type tmp(current++);
			return tmp;
		}

		/**
		 * Advances the iterator by n positions respectively.
		 * @param n position relative to current location
		 * @return *this
		 */
		ft::reverse_iterator<Iter> &operator+=(difference_type n) {
			current -= n;
			return *this;
		}

		/**
		 * Advances the iterator by -n positions respectively.
		 * @param n position relative to current location
		 * @return *this
		 */
		ft::reverse_iterator<Iter> &operator-=(difference_type n) {
			current += n;
			return *this;
		}

	protected:
		/**
		 * Member objects
		 */
		iterator_type current;
	};

	template <typename T>
	bool operator==(const ft::reverse_iterator<T> &rhs,		const ft::reverse_iterator<T> &lhs)			{ return (lhs.base() == rhs.base()); }
	template <typename U, typename V>
	bool operator==(const ft::reverse_iterator<U> &rhs,		const ft::reverse_iterator<V> &lhs)			{ return (lhs.base() == rhs.base()); }


	template <typename T>
	bool operator!=(const ft::reverse_iterator<T> &rhs, const ft::reverse_iterator<T> &lhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename U, typename V>
	bool operator!=(const ft::reverse_iterator<U> &rhs, const ft::reverse_iterator<V> &lhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename T>
	bool operator>=(const ft::reverse_iterator<T> &rhs, const ft::reverse_iterator<T> &lhs) {
		return (lhs.base() >= rhs.base());
	}

	template <typename U, typename V>
	bool operator>=(const ft::reverse_iterator<U> &rhs, const ft::reverse_iterator<V> &lhs) {
		return (lhs.base() >= rhs.base());
	}

	template <typename T>
	bool operator<=(const ft::reverse_iterator<T> &rhs, const ft::reverse_iterator<T> &lhs) {
		return (lhs.base() <= rhs.base());
	}

	template <typename U, typename V>
	bool operator<=(const ft::reverse_iterator<U> &rhs, const ft::reverse_iterator<V> &lhs) {
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	bool operator>(const ft::reverse_iterator<T> &rhs, const ft::reverse_iterator<T> &lhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename U, typename V>
	bool operator>(const ft::reverse_iterator<U> &rhs, const ft::reverse_iterator<V> &lhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename T>
	bool operator<(const ft::reverse_iterator<T> &rhs, const ft::reverse_iterator<T> &lhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename U, typename V>
	bool operator<(const ft::reverse_iterator<U> &rhs, const ft::reverse_iterator<V> &lhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	ft::reverse_iterator<T> operator+(typename ft::reverse_iterator<T>::difference_type rhs, const ft::reverse_iterator<T> &lhs) {
		return (lhs.base() - rhs);
	}

	template <typename U, typename V>
	ft::reverse_iterator<U> operator+(typename ft::reverse_iterator<U>::difference_type rhs, const ft::reverse_iterator<V> &lhs) {
		return (lhs.base() - rhs);
	}

	template <typename T>
	ft::reverse_iterator<T> operator+(const ft::reverse_iterator<T> &rhs, typename ft::reverse_iterator<T>::difference_type lhs) {
		return (rhs.base() - lhs);
	}

	template <typename U, typename V>
	ft::reverse_iterator<U> operator+(const ft::reverse_iterator<U> &rhs, typename ft::reverse_iterator<V>::difference_type lhs) {
		return (rhs.base() - lhs);
	}

	template <typename T>
	ft::reverse_iterator<T> operator-(const ft::reverse_iterator<T> &rhs, typename ft::reverse_iterator<T>::difference_type lhs) {
		return (rhs.base() + lhs);
	}

	template <typename U, typename V>
	ft::reverse_iterator<U> operator-(const ft::reverse_iterator<U> &rhs, typename ft::reverse_iterator<V>::difference_type lhs) {
		return (rhs.base() + lhs);
	}

	template <typename T>
	typename ft::reverse_iterator<T>::difference_type operator-(const ft::reverse_iterator<T> &rhs, const ft::reverse_iterator<T> &lhs) {
		return (lhs.base() - rhs.base());
	}

	template <typename U, typename V>
	typename ft::reverse_iterator<U>::difference_type operator-(const ft::reverse_iterator<V> &rhs, const ft::reverse_iterator<U> &lhs) {
		return (lhs.base() - rhs.base());
	}

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
		vector_iterator &operator=(const vector_iterator &other) {
			_addr = other._addr;
			return *this;
		}

		/**
		 * Returns the underlying base iterator.
		 * @return the underlying iterator
		 */
		pointer base() const {
			return _addr;
		}

		/**
		 * Returns a reference to the element previous to current.
		 * @return reference to the element previous to current
		 */
		reference operator*() const {
			return *_addr;
		}

		/**
		 * Returns a pointer to the element previous to current.
		 * @return pointer to the element previous to current
		 */
		pointer operator->() const {
			return _addr;
		}

		/**
		 * Returns a reference to the element at specified relative location.
		 * @param n position relative to current location
		 * @return a reference to the element at relative location, that is, base()[-n-1]
		 */
		reference operator[](difference_type n) const {
			return *(_addr + n);
		}

		/**
		 * Pre-increments by one respectively.
		 * @return *this
		 */
		vector_iterator &operator++() {
			++_addr;
			return *this;
		}

		/**
		 * Post-increments by one respectively.
		 * @return a copy of *this that was made before the change
		 */
		vector_iterator operator++(int) {
			vector_iterator tmp = _addr++;
			return tmp;
		}

		/**
		 * Pre-decrements by one respectively.
		 * @return *this
		 */
		vector_iterator &operator--() {
			--_addr;
			return *this;
		}

		/**
		 * Post-decrements by one respectively.
		 * @return a copy of *this that was made before the change
		 */
		vector_iterator operator--(int) {
			vector_iterator tmp = _addr--;
			return tmp;
		}

		/**
		 * Advances the iterator by n positions respectively.
		 * @param n position relative to current location
		 * @return *this
		 */
		vector_iterator &operator+=(difference_type n) {
			_addr += n;
			return *this;
		}

		/**
		 * Advances the iterator by -n positions respectively.
		 * @param n position relative to current location
		 * @return *this
		 */
		vector_iterator &operator-=(difference_type n) {
			_addr -= n;
			return *this;
		}

	protected:
		pointer _addr;
	};

	template <typename T, typename Container>
	bool operator==(const ft::vector_iterator<T, Container> &rhs, const ft::vector_iterator<T, Container> &lhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename U, typename V, typename Container>
	bool operator==(const ft::vector_iterator<U, Container> &rhs, const ft::vector_iterator<V, Container> &lhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename T, typename Container>
	bool operator!=(const ft::vector_iterator<T, Container> &rhs, const ft::vector_iterator<T, Container> &lhs) {
		return (lhs.base() != rhs.base());

	}

	template <typename U, typename V, typename Container>
	bool operator!=(const ft::vector_iterator<U, Container> &rhs, const ft::vector_iterator<V, Container> &lhs) {
		return (lhs.base() != rhs.base());

	}

	template <typename T, typename Container>
	bool operator>=(const ft::vector_iterator<T, Container> &rhs, const ft::vector_iterator<T, Container> &lhs) {
		return (lhs.base() <= rhs.base());

	}

	template <typename U, typename V, typename Container>
	bool operator>=(const ft::vector_iterator<U, Container> &rhs, const ft::vector_iterator<V, Container> &lhs) {
		return (lhs.base() <= rhs.base());

	}

	template <typename T, typename Container>
	bool operator<=(const ft::vector_iterator<T, Container> &rhs, const ft::vector_iterator<T, Container> &lhs) {
		return (lhs.base() >= rhs.base());

	}

	template <typename U, typename V, typename Container>
	bool operator<=(const ft::vector_iterator<U, Container> &rhs, const ft::vector_iterator<V, Container> &lhs) {
		return (lhs.base() >= rhs.base());
	}

	template <typename T, typename Container>
	bool operator>(const ft::vector_iterator<T, Container> &rhs, const ft::vector_iterator<T, Container> &lhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename U, typename V, typename Container>
	bool operator>(const ft::vector_iterator<U, Container> &rhs, const ft::vector_iterator<V, Container> &lhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename T, typename Container>
	bool operator<(const ft::vector_iterator<T, Container> &rhs, const ft::vector_iterator<T, Container> &lhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename U, typename V, typename Container>
	bool operator<(const ft::vector_iterator<U, Container> &rhs, const ft::vector_iterator<V, Container> &lhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename T, typename Container>
	ft::vector_iterator<T, Container> operator+(typename ft::vector_iterator<T, Container>::difference_type rhs, const ft::vector_iterator<T, Container> &lhs) {
		return (lhs.base() + rhs);
	}

	template <typename T, typename Container>
	ft::vector_iterator<T, Container> operator+(const ft::vector_iterator<T, Container> &rhs, typename ft::vector_iterator<T, Container>::difference_type lhs) {
		return (rhs.base() + lhs);
	}

	template <typename T, typename Container>
	ft::vector_iterator<T, Container> operator-(const ft::vector_iterator<T, Container> &rhs, typename ft::vector_iterator<T, Container>::difference_type lhs) {
		return (rhs.base() - lhs);
	}

	template <typename T, typename Container>
	typename ft::vector_iterator<T, Container>::difference_type operator-(const ft::vector_iterator<T, Container> &rhs, const ft::vector_iterator<T, Container> &lhs) {
		return (rhs.base() - lhs.base());
	}

	template <typename U, typename V, typename Container>
	typename ft::vector_iterator<U, Container>::difference_type operator-(const ft::vector_iterator<V, Container> &rhs, const ft::vector_iterator<U, Container> &lhs) {
		return (rhs.base() - lhs.base());
	}

	template<typename T>
	class avl_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
	public:
		/**
		 * Member types
		 */
		typedef typename T::value_type value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference reference;

		/**
		 * Member objects
		 */
		T *_node;
		T *_first_node;
		T *_last_node;
		bool _end;

		/**
		 * Default constructor.
		 */
		avl_iterator() : _node(), _first_node(), _last_node(), _end(false) {}

		/**
		 * Constructor with initialized _addr with T* values.
		 * @param node pointer to set
		 * @param first pointer to set
		 * @param last pointer to set
		 */
		avl_iterator(T *node, T *first, T *last) : _node(node), _first_node(first), _last_node(last), _end(node == nullptr) {}

		/**
		 * Avl iterator is initialized with that of copy.
		 * @param avl_it avl iterator to copy
		 */
		template<typename U>
		avl_iterator(const ft::avl_iterator<U> &avl_it) : _node(avl_it._node), _first_node(avl_it._first_node), _last_node(avl_it._last_node), _end(avl_it._end == nullptr) {}

		/**
		 * Destructor.
		 */
		~avl_iterator() {}

		/**
		 * The underlying iterator is assigned the value of the underlying iterator of other.
		 * @param other iterator adaptor to assign
		 * @return *this
		 */
		ft::avl_iterator<T> &operator=(const ft::avl_iterator<T> &other) {
			_node = other._node;
			_first_node = other._node;
			_last_node = other._last_node;
			_end = other._end;
			return *this;
		}

		/**
		 * Returns a reference to the element previous to current.
		 * @return reference to the element previous to current
		 */
		reference operator*() const {
			return _node->value;
		}

		/**
		 * Returns a pointer to the element previous to current.
		 * @return pointer to the element previous to current
		 */
		pointer operator->() const {
			return base();
		}

		/**
		 * Returns the underlying base iterator.
		 * @return the underlying iterator
		 */
		pointer base() const {
			return &_node->value;
		}

		/**
		 * Pre-increments by one respectively.
		 * @return *this
		 */
		ft::avl_iterator<T> &operator++() {
			T *tmp;

			if (!_node) {
				return *this;
			}
			if (!_node->right) {
				if (_node == _last_node) {
					_end = true;
					_node = nullptr;
					return *this;
				}
				tmp = _node;
				_node = _node->parent;
				while (_node->right && tmp == _node->right) {
					tmp = _node;
					_node = _node->parent;
				}
				return *this;
			}
			_node = _node->right;
			while (_node->left) {
				_node = _node->left;
			}
			return *this;
		}

		/**
		 * Post-increments by one respectively.
		 * @return a copy of *this that was made before the change
		 */
		ft::avl_iterator<T> &operator++(int) {
			ft::avl_iterator<T> tmp(*this);
			++*this;
			return tmp;
		}

		/**
		 * Pre-decrements by one respectively.
		 * @return *this
		 */
		ft::avl_iterator<T> &operator--() {
			T *tmp;

			if (!_node && _end) {
				_node = _last_node;
				_end = false;
				return *this;
			}
			if (!_node) {
				return *this;
			}
			if (!_node->left) {
				if (_node == _first_node) {
					_node = nullptr;
					return *this;
				}
				tmp = _node;
				_node = _node->parent;
				while (_node->left && tmp == _node->left) {
					tmp = _node;
					_node = _node->parent;
				}
				return *this;
			}
			_node = _node->left;
			while (_node == _node->right) {
				_node = _node->right;
			}
			return *this;
		}

		/**
		 * Post-decrements by one respectively.
		 * @return a copy of *this that was made before the change
		 */
		ft::avl_iterator<T> &operator--(int) {
			ft::avl_iterator<T> tmp(*this);
			--*this;
			return tmp;
		}

	};

	/**
	 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
	 * @param lhs iterator adaptors to compare
	 * @param rhs iterator adaptors to compare
	 * @return true if the corresponding comparison yields true, false otherwise
	 */
	template<typename T>
	bool operator==(const ft::avl_iterator<T> &lhs, const ft::avl_iterator<T> &rhs) {
		return lhs._node == rhs._node;
	}

	/**
	 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
	 * @param lhs iterator adaptors to compare
	 * @param rhs iterator adaptors to compare
	 * @return true if the corresponding comparison yields true, false otherwise
	 */
	template<typename U, typename V>
	bool operator==(const ft::avl_iterator<U> &lhs, const ft::avl_iterator<V> &rhs) {
		return lhs._node == rhs._node;
	}

	/**
	 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
	 * @param lhs iterator adaptors to compare
	 * @param rhs iterator adaptors to compare
	 * @return true if the corresponding comparison yields true, false otherwise
	 */
	template<typename T>
	bool operator!=(const ft::avl_iterator<T> &lhs, const ft::avl_iterator<T> &rhs) {
		return lhs._node != rhs._node;
	}

	/**
	 * Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.
	 * @param lhs iterator adaptors to compare
	 * @param rhs iterator adaptors to compare
	 * @return true if the corresponding comparison yields true, false otherwise
	 */
	template<typename U, typename V>
	bool operator!=(const ft::avl_iterator<U> &lhs, const ft::avl_iterator<V> &rhs) {
		return lhs._node != rhs._node;
	}

}

#endif //FT_CONTAINERS_ITERATOR_HPP
