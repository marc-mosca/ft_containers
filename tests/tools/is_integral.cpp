/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:59:13 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/24 12:05:50 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../../includes/tools/is_integral.hpp"

class A {};
struct B {};
enum C {};

int main() {

	std::cout << "* Valid values *" << std::endl;

	std::cout << "bool: " << ft::is_integral<bool>::value << std::endl;
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "char16_t: " << ft::is_integral<char16_t>::value << std::endl;
	std::cout << "char32_t: " << ft::is_integral<char32_t>::value << std::endl;
	std::cout << "wchar_t: " << ft::is_integral<wchar_t>::value << std::endl;
	std::cout << "signed char: " << ft::is_integral<signed char>::value << std::endl;
	std::cout << "short int: " << ft::is_integral<short int>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "long int: " << ft::is_integral<long int>::value << std::endl;
	std::cout << "long long int: " << ft::is_integral<long long int>::value << std::endl;
	std::cout << "unsigned char: " << ft::is_integral<unsigned char>::value << std::endl;
	std::cout << "unsigned short int: " << ft::is_integral<unsigned short int>::value << std::endl;
	std::cout << "unsigned int: " << ft::is_integral<unsigned int>::value << std::endl;
	std::cout << "unsigned long int: " << ft::is_integral<unsigned long int>::value << std::endl;
	std::cout << "unsigned long long int: " << ft::is_integral<unsigned long long int>::value << std::endl << std::endl;

	std::cout << "* Invalid values *" << std::endl;

	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	std::cout << "class: " << ft::is_integral<A>::value << std::endl;
	std::cout << "struct: " << ft::is_integral<B>::value << std::endl;
	std::cout << "enum: " << ft::is_integral<C>::value << std::endl;

	return 0;
}
