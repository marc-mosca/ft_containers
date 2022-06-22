/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:17:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/22 17:56:38 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	
	template < class T1, class T2 >
	struct Pair
	{
		
		//	~~	Members types

		typedef T1	first_type;
		typedef T2	second_type;

		//	~~	Members objects

		first_type	first;
		second_type	second;

		//	~~	Constructors

		Pair() : first(), second()
		{
		}

		Pair( const T1 &x, const T2 &y ) : first(x), second(y)
		{
		}

		template< typename U1, typename U2 >
		Pair( const Pair < U1, U2 > &p ) : first(p.first), second(p.second)
		{
		}

		Pair( const Pair < T1, T2 > &p ) : first(p.first), second(p.second)
		{
		}

		//	~~	Destructor

		~Pair()
		{
		}

		//	~~	Operator

		template < typename U1, typename U2 >
		Pair < T1, T2 >	&operator=( const Pair < U1, U2 > &other )
		{
			this->first = other.first;
			this->second = other.second;
			return ( *this );
		}

	};

	template < typename T1, typename T2 >
	ft::Pair < T1, T2 > make_pair( T1 t, T2 u )
	{
		return ( Pair(t, u) );
	}

}

#endif
