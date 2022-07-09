/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:13:23 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/09 16:03:22 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "../includes/map.hpp"
#include "../includes/stack.hpp"
#include "../includes/vector.hpp"

#include "tests.hpp"
#include <map>
#include <utility>

int main(int argc, char **argv)
{
	std::string choice;
	if (argc != 2)
	{
		std::cout << "No test given, testing vector." << std::endl;
		choice = "vector";
	}
	else
		choice = std::string(argv[1]);
	if (choice == "vector")
		test_vector();
	else if (choice == "stack")
		test_stack();
	else if (choice == "all")
	{
		test_vector();
		test_stack();
	}
	else
		std::cout << "No test for " << choice << std::endl;

	return (0);
}
