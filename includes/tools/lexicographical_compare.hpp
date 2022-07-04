/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:30:06 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/04 17:37:29 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_LEXICOGRAPHICAL_COMPARE_HPP
#define FT_CONTAINERS_LEXICOGRAPHICAL_COMPARE_HPP

namespace ft {

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (*first1 != *first2) {
				return !(
						*first2 == *last2 ||
						*first2 < *first1
						);
			}
		}
		return first1 == last1 && first2 != last2;
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
		for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (*first1 != *first2) {
				return !(
						*first2 == *last2 ||
						comp(*first2, *first1)
						);
			}
		}
		return first1 == last1 && first2 != last2;
	}

}

#endif //FT_CONTAINERS_LEXICOGRAPHICAL_COMPARE_HPP
