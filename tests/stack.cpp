/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:14:33 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/10 17:10:21 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

static void constructors(void)
{
	print_header("Constructor");
	ft::stack<int> q1;
	std::stack<int> q2;
	check("q1.size() == q2.size()", q1.size() == q2.size());
	check("q1.empty() == q2.empty()", q1.empty() == q2.empty());
}

static void front_back(void)
{
	print_header("Front / Back / Push / Pop");
	ft::stack<int> q1;
	std::stack<int> q2;
	q1.push(0);
	q1.push(1);
	q1.push(2);
	q2.push(0);
	q2.push(1);
	q2.push(2);
	check("q1.size() == q2.size()", q1.size() == q2.size());
	check("q1.empty() == q2.empty()", q1.empty() == q2.empty());
	check("q1.top() == q2.top()", q1.top(), q2.top());
//	q1.pop();
	q2.pop();
	std::cout << q1.size() << std::endl;
	std::cout << q2.size() << std::endl;
	check("q1.size() == q2.size()", q1.size() == q2.size());
	check("q1.top() == q2.top()", q1.top(), q2.top());
}

void test_stack(void)
{
	print_header("stack");
	constructors();
	front_back();
}
