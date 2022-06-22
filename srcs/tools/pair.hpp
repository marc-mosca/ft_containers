/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:17:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/22 17:31:41 by mmosca           ###   ########lyon.fr   */
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

		//	~~	Constructors

		pair() : first(), second()
		{
		}

		pair( const T1& x, const T2& y ) : first(x), second(y)
		{
		}

		template< class U1, class U2 >
		pair( const pair<U1, U2>& p ) : first(p.first), second(p.second)
		{
		}

	};

}

#endif
