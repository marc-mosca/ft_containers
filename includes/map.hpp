/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:13:30 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/12 17:34:59 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <functional>
#include <memory>
#include <map>
#include "utility.hpp"
#include "algorithm.hpp"
#include "iterator.hpp"
#include "avl.hpp"

namespace ft {

	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:
		/**
		 * Member types.
		 */
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef size_t size_type;
		typedef Allocator allocator_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef typename ft::avl_tree<key_type, mapped_type>::iterator iterator;
		typedef typename ft::avl_tree<key_type, mapped_type>::const_iterator const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

		/**
		 * Member classes.
		 */
		class value_compare : public std::binary_function<value_type, value_type, bool> {
		public:
			friend class map<key_type, mapped_type, key_compare, Allocator>;
			bool operator()(const value_type &x, const value_type &y) const {
				return comp(x.first, y.first);
			}
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}
		};

		/**
		 * Constructs an empty container.
		 * @param comp comparison function object to use for all comparisons of keys
		 * @param alloc allocator to use for all memory allocations of this container
		 */
		map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _comp(comp), _tree() {}

		/**
		 * Constructs the container with the contents of the range [first, last).
		 * @param first the range to copy the elements from
		 * @param last the range to copy the elements from
		 * @param comp comparison function object to use for all comparisons of keys
		 * @param alloc allocator to use for all memory allocations of this container
		 */
		template<class InputIt>
		map(InputIt first, InputIt last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _comp(comp), _tree() {
			insert(first, last);
		}

		/**
		 * Copy constructor. Constructs the container with the copy of the contents of other..
		 * @param other another container to be used as source to initialize the elements of the container with
		 */
		map(const map &other) : _alloc(other._alloc), _comp(other._comp), _tree() {
			*this = other;
		}

		/**
		 * Destructs the map.
		 */
		~map() {
			clear();
		}

		/**
		 * Copy assignment operator. Replaces the contents with a copy of the contents of other.
		 * @param other another container to use as data source
		 * @return *this
		 */
		map &operator=(const map &other) {
			_tree.clear_tree();
			insert(other.begin(), other.end());
			return *this;
		}

		/**
		 * Returns the allocator associated with the container.
		 * @return the associated allocator
		 */
		allocator_type get_allocator() const {
			return _alloc;
		}

		/**
		 * Returns a reference to the value that is mapped to a key equivalent to key, performing an insertion if such key does not already exist.
		 * @param key the key of the element to find
		 * @return reference to the mapped value of the new element if no element with key key existed
		 */
		mapped_type &operator[](const key_type &key) {
			iterator tmp = find(key);

			if (tmp == end()) {
				insert(ft::make_pair(key, mapped_type()));
			}
			tmp = find(key);
			return tmp->second;
		}

		/**
		 * Returns an iterator to the first element of the map.
		 * @return iterator to the first element
		 */
		iterator begin() {
			return _tree.begin();
		}

		/**
		 * Returns an const iterator to the first element of the map.
		 * @return const iterator to the first element
		 */
		const_iterator begin() const {
			return _tree.begin();
		}

		/**
		 * Returns an iterator to the element following the last element of the map.
		 * @return iterator to the element following the last element
		 */
		iterator end() {
			return _tree.end();
		}

		/**
		 * Returns an const iterator to the element following the last element of the map.
		 * @return const iterator to the element following the last element
		 */
		const_iterator end() const {
			return _tree.end();
		}

		/**
		 * Returns a reverse iterator to the first element of the reversed map.
		 * @return reverse iterator to the first element
		 */
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		/**
		 * Returns a const reverse iterator to the first element of the reversed map.
		 * @return const reverse iterator to the first element
		 */
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}

		/**
		 * Returns a reverse iterator to the element following the last element of the reversed map.
		 * @return reverse iterator to the element following the last element
		 */
		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		/**
		 * Returns a cons reverse iterator to the element following the last element of the reversed map.
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
			return _tree.isEmpty();
		}

		/**
		 * Returns the number of elements in the container.
		 * @return the number of elements in the container
		 */
		size_type size() const {
			return _tree.getSize();
		}

		/**
		 * Returns the maximum number of elements the container is able to hold due to system or library implementation limitations.
		 * @return maximum number of elements
		 */
		size_type max_size() const {
			return std::map<key_type, mapped_type>().max_size();
		}

		/**
		 * Erases all elements from the container.
		 */
		void clear() {
			_tree.clear_tree();
		}

		/**
		 * Inserts element(s) into the container, if the container doesn't already contain an element with an equivalent key.
		 * @param value element value to insert
		 * @return Returns a pair consisting of an iterator to the inserted element and a bool denoting whether the insertion took place
		 */
		ft::pair<iterator, bool> insert(const value_type &value) {
			typename avl_tree<key_type, mapped_type>::size_type previousSize = _tree.getSize();
			_tree.insert(value);
			return ft::make_pair(find(value.first), previousSize != _tree.getSize());
		}

		/**
		 * Inserts value in the position as close as possible, to hint.
		 * @param hint iterator, used as a suggestion as to where to start the search
		 * @param value element value to insert
		 * @return returns an iterator to the inserted element, or to the element that prevented the insertion
		 */
		iterator insert(iterator hint, const value_type &value) {
			(void) hint;
			return insert(value).first;
		}

		/**
		 * Inserts elements from range [first, last).
		 * @param first range of elements to insert
		 * @param last range of elements to insert
		 */
		template<class InputIt>
		void insert(InputIt first, InputIt last) {
			while (first != last) {
				_tree.insert(ft::make_pair((key_type)(*first).first, (*first).second));
				first++;
			}
		}

		/**
		 * Removes the element at pos.
		 * @param pos iterator to the element to remove
		 */
		void erase(iterator pos) {
			erase((*pos).first);
		}

		/**
		 * Removes the elements in the range [first; last), which must be a valid range in *this.
		 * @param first range of elements to remove
		 * @param last range of elements to remove
		 */
		void erase(iterator first, iterator last) {
			while (first != last) {
				iterator next = first;
				next++;
				erase(first);
				first = next;
			}
		}

		/**
		 * Removes the element (if one exists) with the key equivalent to key.
		 * @param key key value of the elements to remove
		 * @return Number of elements removed (0 or 1).
		 */
		size_type erase(const key_type &key) {
			if (find(key) == end()) {
				return 0;
			}
			_tree.remove(*find(key));
			return 1;
		}

		/**
		 * Exchanges the contents of the container with those of other.
		 * @param other container to exchange the contents with
		 */
		void swap(map &other) {
			_tree.swap(other._tree);
		}

		/**
		 * Returns the number of elements with key that compares equivalent to the specified argument, which is either 1 or 0 since this container does not allow duplicates.
		 * @param key key value of the elements to count
		 * @return number of elements with key that compares equivalent to key or x, which is either 1 or 0
		 */
		size_type count(const key_type &key) const {
			return find(key) == end() ? 0 : 1;
		}

		/**
		 * Finds an element with key equivalent to key.
		 * @param key key value of the element to search for
		 * @return iterator to an element with key equivalent to key
		 */
		iterator find(const key_type &key) {
			if (_tree.getRoot()) {
				return iterator(_tree.find(ft::make_pair(key, mapped_type())), _tree.getRoot()->getMin(), _tree.getRoot()->getMax());
			}
			return end();
		}

		/**
		 * Finds an element with key equivalent to key.
		 * @param key key value of the element to search for
		 * @return const iterator to an element with key equivalent to key
		 */
		const_iterator find(const key_type &key) const {
			if (_tree.getRoot()) {
				return const_iterator(_tree.find(ft::make_pair(key, mapped_type())), _tree.getRoot()->getMin(), _tree.getRoot()->getMax());
			}
			return end();
		}

		/**
		 * Returns a range containing all elements with the given key in the container.
		 * @param key key value to compare the elements to
		 * @return ft::pair containing a pair of iterators defining the wanted range: the first pointing to the first element that is not less than key and the second pointing to the first element greater than key
		 */
		ft::pair<iterator, iterator> equal_range(const key_type &key) {
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}

		/**
		 * Returns a range containing all elements with the given key in the container.
		 * @param key key value to compare the elements to
		 * @return ft::pair containing a pair of const iterators defining the wanted range: the first pointing to the first element that is not less than key and the second pointing to the first element greater than key
		 */
		ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}

		/**
		 * Returns an iterator pointing to the first element that is not less than key.
		 * @param key key value to compare the elements to
		 * @return iterator pointing to the first element that is not less than key
		 */
		iterator lower_bound(const key_type &key) {
			iterator first = begin();
			iterator last = end();

			while (first != last) {
				if (!_comp((*first).first, key)) {
					break ;
				}
				first++;
			}
			return first;
		}

		/**
		 * Returns an const iterator pointing to the first element that is not less than key.
		 * @param key key value to compare the elements to
		 * @return const iterator pointing to the first element that is not less than key
		 */
		const_iterator lower_bound(const key_type &key) const {
			const_iterator first = begin();
			const_iterator last = end();

			while (first != last) {
				if (!_comp((*first).first, key)) {
					break ;
				}
				first++;
			}
			return first;
		}

		/**
		 * Returns an iterator pointing to the first element that is greater than key.
		 * @param key key value to compare the elements to
		 * @return iterator pointing to the first element that is greater than key
		 */
		iterator upper_bound(const key_type &key) {
			iterator first = begin();
			iterator last = end();

			while (first != last) {
				if (_comp(key, (*first).first)) {
					break ;
				}
				first++;
			}
			return first;
		}

		/**
		 * Returns an const iterator pointing to the first element that is greater than key.
		 * @param key key value to compare the elements to
		 * @return const iterator pointing to the first element that is greater than key
		 */
		const_iterator upper_bound(const key_type &key) const {
			const_iterator first = begin();
			const_iterator last = end();

			while (first != last) {
				if (_comp(key, (*first).first)) {
					break ;
				}
				first++;
			}
			return first;
		}

		/**
		 * Returns the function object that compares the keys, which is a copy of this container's constructor argument comp.
		 * @return the key comparison function object
		 */
		key_compare key_comp() const {
			return key_compare();
		}

		/**
		 * Returns a function object that compares objects of type ft::map::value_type by using key_comp to compare the first components of the pairs.
		 * @return
		 */
		value_compare value_comp() const {
			return value_compare(key_compare());
		}

		/**
		 * Checks if the contents of lhs and rhs are equal, that is, they have the same number of elements and each element in lhs compares equal with the element in rhs at the same position.
		 * @param lhs maps whose contents to compare
		 * @param rhs maps whose contents to compare
		 * @return true if the contents of the maps are equal, false otherwise
		 */
		friend bool operator==(const map &lhs, const map &rhs) {
			return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		/**
		 * Checks if the contents of lhs and rhs are equal, that is, they have the same number of elements and each element in lhs compares equal with the element in rhs at the same position.
		 * @param lhs maps whose contents to compare
		 * @param rhs maps whose contents to compare
		 * @return true if the contents of the maps are not equal, false otherwise
		 */
		friend bool operator!=(const map &lhs, const map &rhs) {
			return !(lhs == rhs);
		}

		/**
		 * Compares the contents of lhs and rhs lexicographically.
		 * @param lhs maps whose contents to compare
		 * @param rhs maps whose contents to compare
		 * @return true if the contents of the lhs are lexicographically less than the contents of rhs, false otherwise
		 */
		friend bool operator<(const map &lhs, const map &rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		/**
		 * Compares the contents of lhs and rhs lexicographically.
		 * @param lhs maps whose contents to compare
		 * @param rhs maps whose contents to compare
		 * @return true if the contents of the lhs are lexicographically less than or equal to the contents of rhs, false otherwise
		 */
		friend bool operator<=(const map &lhs, const map &rhs) {
			return !(lhs > rhs);
		}

		/**
		 * Compares the contents of lhs and rhs lexicographically.
		 * @param lhs maps whose contents to compare
		 * @param rhs maps whose contents to compare
		 * @return true if the contents of the lhs are lexicographically greater than the contents of rhs, false otherwise
		 */
		friend bool operator>(const map &lhs, const map &rhs) {
			return rhs < lhs;
		}

		/**
		 * Compares the contents of lhs and rhs lexicographically.
		 * @param lhs maps whose contents to compare
		 * @param rhs maps whose contents to compare
		 * @return true if the contents of the lhs are lexicographically greater than or equal to the contents of rhs, false otherwise
		 */
		friend bool operator>=(const map &lhs, const map &rhs) {
			return !(lhs < rhs);
		}

		/**
		 * Specializes the ft::swap algorithm for ft::map.
		 * @param lhs containers whose contents to swap
		 * @param rhs containers whose contents to swap
		 */
		friend void swap(map &lhs, map &rhs) {
			lhs.swap(rhs);
		}

	private:
		/**
		 * Member objects
		 */
		allocator_type _alloc;
		key_compare _comp;
		avl_tree<key_type, mapped_type> _tree;
	};

}

#endif //FT_CONTAINERS_MAP_HPP
