/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:06:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/24 11:40:11 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft {

	template<bool is_integral, typename T>
	struct is_integral_res {
		typedef T	type;
		static const bool value = is_integral;
	};

	typedef is_integral_res<false, bool>	false_type;

	template<typename>
	struct is_integral_type : public false_type {};

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

#endif
