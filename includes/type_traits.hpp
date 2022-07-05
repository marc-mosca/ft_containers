/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:49:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/05 11:49:58 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

namespace ft {

	//	~~	ENABLE_IF ----------------------------------------------------------

	template<bool B, class T = void>
	struct enable_if {};

	template<class T = void>
	struct enable_if<true, T> {
		typedef T type;
	};

	//	~~	IS_INTEGRAL --------------------------------------------------------

	template<bool is_integral, typename T>
	struct is_integral_res {
		typedef T type;
		static const bool value = is_integral;
	};

	template<typename>
	struct is_integral_type : public is_integral_res<false, bool> {};
	template<>
	struct is_integral_type<bool> : public is_integral_res<true, bool> {};
	template<>
	struct is_integral_type<char> : public is_integral_res<true, char> {};
	template<>
	struct is_integral_type<char16_t> : public is_integral_res<true, char16_t> {};
	template<>
	struct is_integral_type<char32_t> : public is_integral_res<true, char32_t> {};
	template<>
	struct is_integral_type<wchar_t> : public is_integral_res<true, wchar_t> {};
	template<>
	struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};
	template<>
	struct is_integral_type<short int> : public is_integral_res<true, short int> {};
	template<>
	struct is_integral_type<int> : public is_integral_res<true, int> {};
	template<>
	struct is_integral_type<long int> : public is_integral_res<true, long int> {};
	template<>
	struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};
	template<>
	struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};
	template<>
	struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};
	template<>
	struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};
	template<>
	struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
	template<>
	struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

	template<typename T>
	struct is_integral : public is_integral_type<T> {};

}

#endif //FT_CONTAINERS_TYPE_TRAITS_HPP
