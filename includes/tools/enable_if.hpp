/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:03:45 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/04 17:04:59 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ENABLE_IF_HPP
#define FT_CONTAINERS_ENABLE_IF_HPP

namespace ft {

	template<bool B, class T = void>
	struct enable_if {};

	template<class T = void>
	struct enable_if<true, T> {
		typedef T type;
	};

}

#endif //FT_CONTAINERS_ENABLE_IF_HPP
