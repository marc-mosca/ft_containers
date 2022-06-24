/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:15:54 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/22 16:35:28 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

namespace ft {

	template<class T, class Container = std::vector<T> >
	class stack {

	public:
		typedef Container	container_type;
		typedef typename Container::value_type	value_type;
		typedef typename Container::size_type	size_type;
		typedef typename Container::reference	reference;
		typedef typename Container::const_reference	const_reference;

		explicit stack(const Container &cont = Container());
		~stack();
		stack &operator=(const stack &other);
		reference top();
		const_reference top() const;
		bool empty() const;
		size_type size() const;
		void push(const value_type &value);
		void pop();

		template<class Tx, class Containerx>
		friend bool operator==(const ft::stack<Tx, Containerx> &lhs, const ft::stack<Tx, Containerx> &rhs);
		template<class Tx, class Containerx>
		friend bool operator!=(const ft::stack<Tx, Containerx> &lhs, const ft::stack<Tx, Containerx> &rhs);
		template<class Tx, class Containerx>
		friend bool operator<(const ft::stack<Tx, Containerx> &lhs, const ft::stack<Tx, Containerx> &rhs);
		template<class Tx, class Containerx>
		friend bool operator<=(const ft::stack<Tx, Containerx> &lhs, const ft::stack<Tx, Containerx> &rhs);
		template<class Tx, class Containerx>
		friend bool operator>(const ft::stack<Tx, Containerx> &lhs, const ft::stack<Tx, Containerx> &rhs);
		template<class Tx, class Containerx>
		friend bool operator>=(const ft::stack<Tx, Containerx> &lhs, const ft::stack<Tx, Containerx> &rhs);

	protected:
		container_type c;

	};

	//	~~	Constructor

	template<class T, class Container>
	stack<T, Container>::stack(const Container &cont) : c(cont) {}

	//	~~	Destructor

	template<class T, class Container>
	stack<T, Container>::~stack() {}

	//	~~	Operator

	template<class T, class Container>
	stack<T, Container> &stack<T, Container>::operator=(const stack<T, Container> &other) {
		this->c = other.c;
		return *this;
	}

	//	~~	Element Access

	template<class T, class Container>
	typename stack<T, Container>::reference stack<T, Container>::top() {
		return this->c.back();
	}

	template<class T, class Container>
	typename stack<T, Container>::const_reference stack<T, Container>::top() const {
		return this->c.back();
	}

	//	~~	Capacity

	template<class T, class Container>
	bool stack<T, Container>::empty() const {
		return (this->size() == 0);
	}

	template<class T, class Container>
	typename stack<T, Container>::size_type stack<T, Container>::size() const {
		return this->c.size();
	}

	//	~~	Modifiers

	template<class T, class Container>
	void stack<T, Container>::push(const value_type &value) {
		this->c.push_back(value);
	}

	template<class T, class Container>
	void stack<T, Container>::pop() {
		this->c.pop_back();
	}

	//	~~	Non-member functions

	template<class Tx, class Containerx>
	bool operator==(const stack<Tx, Containerx> &lhs, const stack<Tx, Containerx> &rhs) {
		return (lhs.c == rhs.c);
	}

	template<class Tx, class Containerx>
	bool operator!=(const stack<Tx, Containerx> &lhs, const stack<Tx, Containerx> &rhs) {
		return (lhs.c != rhs.c);
	}

	template<class Tx, class Containerx>
	bool operator<(const stack<Tx, Containerx> &lhs, const stack<Tx, Containerx> &rhs) {
		return (lhs.c < rhs.c);
	}

	template<class Tx, class Containerx>
	bool operator<=(const stack<Tx, Containerx> &lhs, const stack<Tx, Containerx> &rhs) {
		return (lhs.c <= rhs.c);
	}

	template<class Tx, class Containerx>
	bool operator>(const stack<Tx, Containerx> &lhs, const stack<Tx, Containerx> &rhs) {
		return (lhs.c > rhs.c);
	}

	template<class Tx, class Containerx>
	bool operator>=(const stack<Tx, Containerx> &lhs, const stack<Tx, Containerx> &rhs) {
		return (lhs.c >= rhs.c);
	}

}

#endif // STACK_HPP
