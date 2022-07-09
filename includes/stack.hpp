/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:55:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/09 15:34:14 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft {

	/**
	 * The ft::stack class is a container adaptor that gives the programmer the functionality of a stack - specifically, a LIFO (last-in, first-out) data structure.
	 * @tparam T the type of the stored elements
	 * @tparam Container the type of the underlying container to use to store the elements
	 */
	template<class T, class Container = ft::vector<T> >
	class stack {
	public:
		/**
		 * Member types
		 */
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		/**
		 * Copy-constructs the underlying container c with the contents of cont.
		 * @param cont container to be used as source to initialize the underlying container
		 */
		explicit stack(const container_type &cont = container_type()) : c(cont) {}

		/**
		 * Destructs the stack.
		 */
		~stack() {}

		/**
		 * Copy assignment operator. Replaces the contents with a copy of the contents of other.
		 * @param other another container adaptor to be used as source
		 * @return *this
		 */
		ft::stack<T, Container> &operator=(const ft::stack<T, Container> &other) {
			c = other.c;
			return *this;
		}

		/**
		 * Returns reference to the top element in the stack. This is the most recently pushed element.
		 * @return reference to the last element
		 */
		reference top() {
			return c.back();
		}

		/**
		 * Returns const reference to the top element in the stack. This is the most recently pushed element.
		 * @return const reference to the last element
		 */
		const_reference top() const {
			return c.back();
		}

		/**
		 * Checks if the underlying container has no elements.
		 * @return true if the underlying container is empty, false otherwise
		 */
		bool empty() const {
			return c.empty();
		}

		/**
		 * Returns the number of elements in the underlying container.
		 * @return the number of elements in the container
		 */
		size_type size() const {
			return c.size();
		}

		/**
		 * Pushes the given element value to the top of the stack.
		 * @param value the value of the element to push
		 */
		void push(const value_type &value) {
			c.push_back(value);
		}

		/**
		 * Removes the top element from the stack.
		 */
		void pop() {
			c.pop_back();
		}

		/**
		 * Compares the contents of the underlying containers of two container adaptors. The comparison is done by applying the corresponding operator to the underlying containers.
		 * @param lhs container adaptors whose contents to compare
		 * @param rhs container adaptors whose contents to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Tx, class Cx>
		friend bool operator==(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
			return lhs.c == rhs.c;
		}

		/**
		 * Compares the contents of the underlying containers of two container adaptors. The comparison is done by applying the corresponding operator to the underlying containers.
		 * @param lhs container adaptors whose contents to compare
		 * @param rhs container adaptors whose contents to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Tx, class Cx>
		friend bool operator!=(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
			return lhs.c != rhs.c;
		}

		/**
		 * Compares the contents of the underlying containers of two container adaptors. The comparison is done by applying the corresponding operator to the underlying containers.
		 * @param lhs container adaptors whose contents to compare
		 * @param rhs container adaptors whose contents to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Tx, class Cx>
		friend bool operator<(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
			return lhs.c < rhs.c;
		}

		/**
		 * Compares the contents of the underlying containers of two container adaptors. The comparison is done by applying the corresponding operator to the underlying containers.
		 * @param lhs container adaptors whose contents to compare
		 * @param rhs container adaptors whose contents to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Tx, class Cx>
		friend bool operator<=(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
			return lhs.c <= rhs.c;
		}

		/**
		 * Compares the contents of the underlying containers of two container adaptors. The comparison is done by applying the corresponding operator to the underlying containers.
		 * @param lhs container adaptors whose contents to compare
		 * @param rhs container adaptors whose contents to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Tx, class Cx>
		friend bool operator>(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
			return lhs.c > rhs.c;
		}

		/**
		 * Compares the contents of the underlying containers of two container adaptors. The comparison is done by applying the corresponding operator to the underlying containers.
		 * @param lhs container adaptors whose contents to compare
		 * @param rhs container adaptors whose contents to compare
		 * @return true if the corresponding comparison yields true, false otherwise
		 */
		template<class Tx, class Cx>
		friend bool operator>=(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
			return lhs.c >= rhs.c;
		}
	protected:
		/**
		 * Member objects
		 */
		container_type c;
	};

}

#endif //FT_CONTAINERS_STACK_HPP
