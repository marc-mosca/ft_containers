/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:04:11 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/09 20:12:04 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>
#include <iostream>
#include <algorithm>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace ft {

	/**
	 * ft::vector is a sequence container that encapsulates dynamic size arrays.
	 * @tparam T the type of the elements
	 * @tparam Allocator an allocator that is used to acquire/release memory and to construct/destroy the elements in that memory
	 */
	template<class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		/**
		 * Member types
		 */
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::vector_iterator<value_type, vector> iterator;
		typedef typename ft::vector_iterator<const value_type, vector> const_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		/**
		 * Default constructor.
		 */
		vector() : _alloc(), _addr(nullptr), _len(0), _capacity(0) {}

		/**
		 * Constructs an empty container with the given allocator alloc.
		 * @param alloc allocator to use for all memory allocations of this container
		 */
		vector(const allocator_type &alloc) : _alloc(alloc), _addr(nullptr), _len(0), _capacity(0) {}

		/**
		 * Constructs the container with count copies of elements with value value.
		 * @param count the size of the container
		 * @param value the value to initialize elements of the container with
		 * @param alloc allocator to use for all memory allocations of this container
		 */
		vector(size_type count, const value_type &value = T(), const allocator_type &alloc = Allocator()) : _alloc(alloc), _addr(nullptr), _len(0), _capacity(0) {
			assign(count, value);
		}

		/**
		 * Constructs the container with the contents of the range [first, last).
		 * @param first the range to copy the elements from
		 * @param last the range to copy the elements from
		 * @param alloc allocator to use for all memory allocations of this container
		 */
		template<class InputIt>
		vector(InputIt first, InputIt last, const allocator_type &alloc = Allocator()) : _alloc(alloc), _addr(nullptr), _len(0), _capacity(0) {
			assign(first, last);
		}

		/**
		 * Copy constructor. Constructs the container with the copy of the contents of other.
		 * @param other another container to be used as source to initialize the elements of the container with
		 */
		vector(const ft::vector<T, Allocator> &other) : _addr(nullptr), _len(0), _capacity(0) {
			*this = other;
		}

		/**
		 * Destructs the vector.
		 */
		~vector() {
			for (size_type i = 0; i < _len; i++) {
				_alloc.destroy(&_addr[i]);
			}
			_alloc.deallocate(_addr, _capacity);
		}

		/**
		 * Copy assignment operator. Replaces the contents with a copy of the contents of other.
		 * @param other another container to use as data source
		 * @return *this
		 */
		ft::vector<T, Allocator> &operator=(const ft::vector<T, Allocator> &other) {
			_alloc = other.get_allocator();
			assign(other.begin(), other.end());
			return *this;
		}

		/**
		 * Replaces the contents with count copies of value value.
		 * @param count the new size of the container
		 * @param value the value to initialize elements of the container with
		 */
		void assign(size_type count, const value_type &value) {
			clear();
			insert(begin(), count, value);
		}

		/**
		 * Replaces the contents with copies of those in the range [first, last).
		 * @param first the range to copy the elements from
		 * @param last the range to copy the elements from
		 */
		template<class InputIt>
		void assign(InputIt first, InputIt last) {
			clear();
			insert(begin(), first, last);
		}

		/**
		 * Returns the allocator associated with the container.
		 * @return the associated allocator
		 */
		allocator_type get_allocator() const {
			return _alloc;
		}

		/**
		 * Returns a reference to the element at specified location pos, with bounds checking.
		 * @param pos position of the element to return
		 * @return reference to the requested element
		 */
		reference at(size_type pos) {
			if (pos < 0 || pos > _len) {
				throw std::out_of_range("index out of range");
			}
			return _addr[pos];
		}

		/**
		 * Returns a const reference to the element at specified location pos, with bounds checking.
		 * @param pos position of the element to return
		 * @return const reference to the requested element
		 */
		const_reference at(size_type pos) const {
			if (pos < 0 || pos > _len) {
				throw std::out_of_range("index out of range");
			}
			return _addr[pos];
		}

		/**
		 * Returns a reference to the element at specified location pos.
		 * @param pos position of the element to return
		 * @return reference to the requested element
		 */
		reference operator[](size_type pos) {
			return *(begin() + pos);
		}

		/**
		 * Returns a const reference to the element at specified location pos.
		 * @param pos position of the element to return
		 * @return const reference to the requested element
		 */
		const_reference operator[](size_type pos) const {
			return *(begin() + pos);
		}

		/**
		 * Returns a reference to the first element in the container.
		 * @return reference to the first element
		 */
		reference front() {
			return *begin();
		}

		/**
		 * Returns a const reference to the first element in the container.
		 * @return const reference to the first element
		 */
		const_reference front() const {
			return *begin();
		}

		/**
		 * Returns a reference to the last element in the container.
		 * @return reference to the last element
		 */
		reference back() {
			return *(end() - (_len > 0));
		}

		/**
		 * Returns a reference to the last element in the container.
		 * @return reference to the last element
		 */
		const_reference back() const {
			return *(end() - (_len > 0));
		}

		/**
		 * Returns an iterator to the first element of the vector.
		 * @return iterator to the first element
		 */
		iterator begin() {
			return iterator(_addr);
		}

		/**
		 * Returns an const iterator to the first element of the vector.
		 * @return const iterator to the first element
		 */
		const_iterator begin() const {
			return const_iterator(_addr);
		}

		/**
		 * Returns an iterator to the element following the last element of the vector.
		 * @return iterator to the element following the last element
		 */
		iterator end() {
			return iterator(_addr + _len);
		}

		/**
		 * Returns an const iterator to the element following the last element of the vector.
		 * @return const iterator to the element following the last element
		 */
		const_iterator end() const {
			return const_iterator(_addr + _len);
		}

		/**
		 * Returns a reverse iterator to the first element of the reversed vector.
		 * @return reverse iterator to the first element
		 */
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		/**
		 * Returns a const reverse iterator to the first element of the reversed vector.
		 * @return const reverse iterator to the first element
		 */
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}

		/**
		 * Returns a reverse iterator to the element following the last element of the reversed vector.
		 * @return reverse iterator to the element following the last element
		 */
		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		/**
		 * Returns a const reverse iterator to the element following the last element of the reversed vector.
		 * @return const reverse iterator to the element following the last element
		 */
		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}

		/**
		 * Checks if the container has no elements.
		 * @return true if the container is empty, false otherwise
		 */
		bool empty() const {
			return _len == 0;
		}

		/**
		 * Returns the number of elements in the container.
		 * @return the number of elements in the container
		 */
		size_type size() const {
			return _len;
		}

		/**
		 * Returns the maximum number of elements the container is able to hold due to system or library implementation limitations.
		 * @return maximum number of elements
		 */
		size_type max_size() const {
			return _alloc.max_size();
		}

		/**
		 * Increase the capacity of the vector to a value that's greater or equal to new_cap.
		 * @param new_cap new capacity of the vector, in number of elements
		 */
		void reserve(size_type new_cap) {
			value_type *addr;

			if (new_cap == 0 || new_cap <= capacity()) {
				return;
			}
			addr = _alloc.allocate(new_cap);
			for (size_type i = 0; i < size(); ++i) {
				_alloc.construct(&addr[i], _addr[i]);
				_alloc.destroy(&_addr[i]);
			}
			_alloc.deallocate(_addr, capacity());
			_capacity = new_cap;
			_addr = addr;
		}

		/**
		 * Returns the number of elements that the container has currently allocated space for.
		 * @return capacity of the currently allocated storage
		 */
		size_type capacity() const {
			return _capacity;
		}

		/**
		 * Erases all elements from the container.
		 */
		void clear() {
			erase(begin(), end());
		}

		/**
		 * Inserts elements at the specified location in the container.
		 * @param pos iterator before which the content will be inserted; pos may be the end() iterator
		 * @param value element value to insert
		 * @return iterator pointing to the inserted value
		 */
		iterator insert(iterator pos, const value_type &value) {
			typename ft::iterator_traits<iterator>::difference_type i = pos - begin();

			insert(pos, 1, value);
			return begin() + i;
		}

		/**
		 * Inserts count copies of the value before pos.
		 * @param pos iterator before which the content will be inserted; pos may be the end() iterator
		 * @param count number of elements to insert
		 * @param value element value to insert
		 */
		void insert(iterator pos, size_type count, const value_type &value) {
			size_type quantity = count;
			size_type index = pos - begin();

			if (quantity <= 0) {
				return;
			}
			while (_len + quantity > _capacity) {
				size_type sizeToReserve = _capacity == 0 ? 1 : _capacity * 2;
				reserve(sizeToReserve);
			}
			if (_len > 0) {
				for (size_type i = _len - 1; i >= index && i != std::numeric_limits<size_type>::max(); --i) {
					_alloc.construct(&_addr[i + quantity], _addr[i]);
					_alloc.destroy(&_addr[i]);
				}
			}
			for (size_type i = index; i < index + quantity; i++) {
				_alloc.construct(&_addr[i], value);
			}
			_len += quantity;
		}

		/**
		 * Inserts elements from range [first, last) before pos.
		 * @param pos iterator before which the content will be inserted. pos may be the end() iterator
		 * @param first the range of elements to insert, can't be iterators into container for which insert is called
		 * @param last the range of elements to insert, can't be iterators into container for which insert is called
		 */
		template<class InputIt>
		void insert(iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr) {
			size_type quantity = ft::distance(first, last);
			size_type index = pos - begin();

			if (quantity <= 0) {
				return;
			}
			while (_len + quantity > _capacity) {
				size_type sizeToReserve = _capacity == 0 ? 1 : _capacity * 2;
				reserve(sizeToReserve);
			}
			if (_len > 0) {
				for (size_type i = _len - 1; i >= index && i != std::numeric_limits<size_type>::max(); i--) {
					_alloc.construct(&_addr[i + quantity], _addr[i]);
					_alloc.destroy(&_addr[i]);
				}
			}
			for (InputIt it = first; it != last; ++it) {
				_alloc.construct(&_addr[index++], *it);
			}
			_len += quantity;
		}

		/**
		 * Erases the specified elements from the container.
		 * @param pos iterator to the element to remove
		 * @return iterator following the last removed element
		 */
		iterator erase(iterator pos) {
			return erase(pos, pos + 1);
		}

		/**
		 * Erases the specified elements from the container.
		 * @param first range of elements to remove
		 * @param last range of elements to remove
		 * @return iterator following the last removed element
		 */
		iterator erase(iterator first, iterator last) {
			size_type dist = ft::distance(first, last);

			if (dist <= 0) {
				return last;
			}
			for (iterator it = first; it != last; it++) {
				_alloc.destroy(&(*it));
			}
			if (last == end()) {
				_len -= dist;
				return end();
			}
			for (iterator it = last; it != end(); it++) {
				_alloc.construct(&(*(it - dist)), *it);
				_alloc.destroy(&(*it));
			}
			_len -= dist;
			return first;
		}

		/**
		 * Appends the given element value to the end of the container.
		 * @param value the value of the element to append
		 */
		void push_back(const value_type &value) {
			insert(end(), value);
		}

		/**
		 * Removes the last element of the container.
		 */
		void pop_back() {
			erase(end() - 1);
		}

		/**
		 * Resizes the container to contain count elements.
		 * @param count new size of the container
		 */
		void resize(size_type count, value_type value = value_type()) {
			if (count == _len) {
				return;
			} else if (count > _len) {
				insert(end(), count - _len, value);
			} else {
				erase(begin() + count, end());
			}
		}

		/**
		 * Exchanges the contents of the container with those of other.
		 * @param other container to exchange the contents with
		 */
		void swap(ft::vector<T, Allocator> &other) {
			std::swap(_alloc, other._alloc);
			std::swap(_addr, other._addr);
			std::swap(_len, other._len);
			std::swap(_capacity, other._capacity);
		}

		/**
		 * Specializes the ft::swap algorithm for ft::vector.
		 * @param v containers whose contents to swap
		 * @param w containers whose contents to swap
		 */
		friend void swap(ft::vector<T, Allocator> &x, ft::vector<T, Allocator> &y) {
			x.swap(y);
		}

		/**
		 * Checks if the contents of lhs and rhs are equal, that is, they have the same number of elements and each element in lhs compares equal with the element in rhs at the same position.
		 * @param lhs vectors whose contents to compare
		 * @param rhs vectors whose contents to compare
		 * @return true if the contents of the vectors are equal, false otherwise
		 */
		friend bool operator==(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs) {
			if (lhs.size() != rhs.size()) {
				return false;
			}
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		/**
		 * Checks if the contents of lhs and rhs are equal, that is, they have the same number of elements and each element in lhs compares equal with the element in rhs at the same position.
		 * @param lhs vectors whose contents to compare
		 * @param rhs vectors whose contents to compare
		 * @return true if the contents of the vectors are not equal, false otherwise
		 */
		friend bool operator!=(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs) {
			return !(lhs == rhs);
		}

		/**
		 * Compares the contents of lhs and rhs lexicographically.
		 * @param lhs vectors whose contents to compare
		 * @param rhs vectors whose contents to compare
		 * @return true if the contents of the lhs are lexicographically less than the contents of rhs, false otherwise
		 */
		friend bool operator<(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		/**
		 * Compares the contents of lhs and rhs lexicographically.
		 * @param lhs vectors whose contents to compare
		 * @param rhs vectors whose contents to compare
		 * @return true if the contents of the lhs are lexicographically less than or equal to the contents of rhs, false otherwise
		 */
		friend bool operator<=(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs) {
			return !(lhs > rhs);
		}

		/**
		 * Compares the contents of lhs and rhs lexicographically.
		 * @param lhs vectors whose contents to compare
		 * @param rhs vectors whose contents to compare
		 * @return true if the contents of the lhs are lexicographically greater than the contents of rhs, false otherwise
		 */
		friend bool operator>(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs) {
			return rhs < lhs;
		}

		/**
		 * Compares the contents of lhs and rhs lexicographically.
		 * @param lhs vectors whose contents to compare
		 * @param rhs vectors whose contents to compare
		 * @return true if the contents of the lhs are lexicographically greater than or equal to the contents of rhs, false
		 */
		friend bool operator>=(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs) {
			return !(lhs < rhs);
		}

	private:
		/**
		 * Member objects
		 */
		allocator_type _alloc;
		pointer _addr;
		size_type _len;
		size_type _capacity;
	};

}

#endif //FT_CONTAINERS_VECTOR_HPP
