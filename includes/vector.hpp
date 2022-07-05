/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:15:00 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/05 12:39:24 by mmosca           ###   ########.fr       */
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

	private:
		allocator_type _alloc;
		pointer _addr;
		size_type _len;
		size_type _cap;
	};

}

#endif //FT_CONTAINERS_VECTOR_HPP
