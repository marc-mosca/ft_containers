/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:14:22 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/04 13:30:05 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include <vector>

namespace ft {

	template<class T, class Container = std::vector<T> >
	class stack {
	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		explicit stack(const Container &cont = Container()): c(cont) {}
		~stack() {}
		stack &operator=(const stack &other) {
			this->c = other.c;
			return *this;
		}
		reference top() {
			return this->c.back();
		}
		const_reference top() const {
			return this->c.back();
		}
		bool empty() const {
			return this->size() == 0;
		}
		size_type size() const {
			return this->c.size();
		}
		void push(const value_type &value) {
			this->c.push_back(value);
		}
		void pop() {
			this->c.pop_back();
		}

		template<class Tx, class Cx>
		friend bool operator==(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs);
		template<class Tx, class Cx>
		friend bool operator!=(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs);
		template<class Tx, class Cx>
		friend bool operator<(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs);
		template<class Tx, class Cx>
		friend bool operator<=(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs);
		template<class Tx, class Cx>
		friend bool operator>(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs);
		template<class Tx, class Cx>
		friend bool operator>=(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs);

	private:
		container_type c;
	};

	template<class Tx, class Cx>
	bool operator==(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
		return lhs.c == rhs.c;
	}
	template<class Tx, class Cx>
	bool operator!=(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
		return lhs.c != rhs.c;
	}
	template<class Tx, class Cx>
	bool operator<(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
		return lhs.c < rhs.c;
	}
	template<class Tx, class Cx>
	bool operator<=(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
		return lhs.c <= rhs.c;
	}
	template<class Tx, class Cx>
	bool operator>(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
		return lhs.c > rhs.c;
	}
	template<class Tx, class Cx>
	bool operator>=(const ft::stack<Tx, Cx> &lhs, const ft::stack<Tx, Cx> &rhs) {
		return lhs.c >= rhs.c;
	}

}

#endif //FT_CONTAINERS_STACK_HPP
