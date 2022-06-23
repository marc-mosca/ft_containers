/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:06:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/23 15:06:51 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft
{

	template<class T, T v>
	struct integral_constant {

		//	~~	Member types

		typedef T	value_type;
		typedef integral_constant<T, v>	type;

		//	~~	Member constant

		const static T value = v;

		//	~~	Member function

		operator value_type() const;

	};

	template<class T, T v>
	integral_constant<T, v>::value_type() {
		return value;
	}

	typedef ft::integral_constant<bool, true>	true_type;
	typedef ft::integral_constant<bool, false>	false_type;

	template<class T>
	struct is_integral {

		//	~~	Member type

		typedef bool	value_type;

	};

}

#endif
