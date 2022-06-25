/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:44:07 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/25 11:19:23 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft {

	template<bool B, class T = void>
	struct enable_if {};

	template<class T = void>
	struct enable_if<true, T> {
		typedef T	type;
	};

}

#endif // ENABLE_IF_HPP
