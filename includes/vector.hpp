/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:15:00 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/05 18:19:43 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>
#include <iostream>
#include <algorithm>
#include "iterator.hpp"

namespace ft {

	template<class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef allocator_type::reference reference;
		typedef allocator_type::const_reference const_reference;
		typedef allocator_type::pointer pointer;
		typedef allocator_type::const_pointer const_pointer;
		typedef ft::vector_iterator<value_type, vector> iterator;
		typedef ft::vector_iterator<const value_type, vector> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _addr(nullptr), _len(0), _cap(0) {}
		vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _addr(nullptr), _len(0), _cap(0) {
			assign(n, val);
		}
		template<class Iter>
		vector(Iter first, Iter last, const allocator_type &alloc = allocator_type()) : _alloc(alloc), _addr(nullptr), _len(0), _cap(0) {
			assign(first, last);
		}
		vector(const vector &copy) : _addr(nullptr), _len(0), _cap(0) {
			*this = copy;
		}
		~vector() {
			for (size_type i = 0; i < this->_len; ++i) {
				this->_alloc.destroy(&this->_addr[i]);
			}
			this->_alloc.deallocate(this->_addr, this->_cap);
		}
		vector &operator=(const vector &other) {
			this->_alloc = other._alloc;
			assign(other.begin(), other.end());
			return *this;
		}
		void assign(size_type count, const value_type &value) {
			clear();
			insert(begin(), count, value);
		}
		template<class InputIt>
		void assign(InputIt first, InputIt last) {
			clear();
			insert(begin(), first, last);
		}
		allocator_type get_allocator() const {
			return this->_alloc;
		}
		reference at(size_type pos) {
			if (pos < 0 || pos >= this->_len) {
				throw std::out_of_range("index out of range");
			}
			return this->_addr[pos];
		}
		const_reference at(size_type pos) const {
			if (pos < 0 || pos >= this->_len) {
				throw std::out_of_range("index out of range");
			}
			return this->_addr[pos];
		}
		reference operator[](size_type pos) {
			return *(begin() + pos);
		}
		const_reference operator[](size_type pos) const {
			return *(begin() + pos);
		}
		reference front() {
			return *begin();
		}
		const_reference front() const {
			return *begin();
		}
		reference back() {
			return *(end() - (this->_len > 0));
		}
		const_reference back() const {
			return *(end() - (this->_len > 0));
		}
		iterator begin() {
			return iterator(this->_addr);
		}
		const_iterator begin() const {
			return const_iterator(this->_addr);
		}
		iterator end() {
			return iterator(this->_addr + this->_len);
		}
		const_iterator end() const {
			return const_iterator(this->_addr + this->_len);
		}
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() {
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}
		bool empty() const {
			return this->_len == 0;
		}
		size_type size() const {
			return this->_len;
		}
		size_type max_size() const {
			return this->_alloc.max_size();
		}
		void reserve(size_type cap) {
			if (cap == 0 || cap <= this->_cap) {
				return;
			}
			value_type *addr = this->_alloc.allocate(cap);
			for (size_type i = 0; i < this->_len; ++i) {
				this->_alloc.construct(&addr[i], this->_addr[i]);
				this->_alloc.destroy(&this->_addr[i]);
			}
			this->_alloc.deallocate(this->_addr, this->_cap);
			this->_cap = cap;
			this->_addr = addr;
		}
		size_type capacity() const {
			return this->_cap;
		}
		void clear() {
			erase(begin(), end());
		}
		iterator insert(iterator pos, const value_type &value) {
			typename iterator_traits<iterator>::difference_type i = pos - this->begin();
			this->insert(pos, 1, value);
			return this->begin() + i;
		}
		void insert(iterator pos, size_type count, const value_type &value) {
			size_type quantity = count;
			size_type i = pos - this->begin();

			if (quantity <= 0) {
				return;
			}
			while (this->_len + quantity > this->_cap) {
				this->reserve(this->_cap == 0 ? 1 : this->_cap * 2);
				quantity++;
			}
 			if (this->_len > 0) {
				 for (size_type j = this->_len - 1; j >= i && j != std::numeric_limits<size_type>::max(); j--) {
					 this->_alloc.construct(&this->_addr[j + quantity], this->_addr[j]);
					 this->_alloc.destroy(&this->_addr[j]);
				 }
			}
			for (size_type j = i; j < i + quantity; j++) {
				this->_alloc.construct(&this->_addr[j], value);
			}
			this->_len += quantity;
		}
		template<class InputIt>
		void insert(iterator pos, InputIt first, InputIt last) {
			size_type quantity = ft::distance(first, last);
			size_type i = pos - this->begin();

			if (quantity <= 0) {
				return;
			}
			while (this->_len + quantity > this->_cap) {
				this->reserve(this->_cap == 0 ? 1 : this->_cap * 2);
				quantity++;
			}
			if (this->_len > 0) {
				for (size_type j = this->_len - 1; j >= i && j != std::numeric_limits<size_type>::max(); j--) {
					this->_alloc.construct(&this->_addr[j + quantity], this->_addr[j]);
					this->_alloc.destroy(&this->_addr[j]);
				}
			}
			for (size_type j = i; j < i + quantity; j++) {
				this->_alloc.construct(&this->_addr[j], value);
			}
			this->_len += quantity;
		}
		iterator erase(iterator pos) {
			return this->erase(pos, pos + 1);
		}
		iterator erase(iterator first, iterator last) {
			size_type dist = ft::distance(first, last);

			if (dist <= 0) {
				return last;
			}
			for (iterator it = first; it != last; it++) {
				this->_alloc.destroy(&(*it));
			}
			if (last == this->end()) {
				this->_len -= dist;
				return this->end();
			}
			for (iterator it = last; it != this->end(); it++) {
				this->_alloc.construct(&(*(it - dist)), *it);
				this->_alloc.destroy(&(*it));
			}
			this->_len -= dist;
			return first;
		}

	private:
		allocator_type _alloc;
		pointer _addr;
		size_type _len;
		size_type _cap;
	};

}

#endif //FT_CONTAINERS_VECTOR_HPP
