/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:17:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/22 17:21:01 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	
	template < class T1, class T2 >
	struct pair
	{
		
		//	~~	Members types

		typedef T1	first_type;
		typedef T2	second_type;

		//	~~	Members objects

		first_type	first;
		second_type	second;

	};

}

#endif
