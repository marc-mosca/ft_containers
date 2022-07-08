/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:15:11 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/08 13:30:26 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ALGORITHM_HPP
#define FT_CONTAINERS_ALGORITHM_HPP

namespace ft {

	/**
	 * Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), and false otherwise.
	 * @param first the first range of the elements to compare
	 * @param last the first range of the elements to compare
	 * @param first2 the second range of the elements to compare
	 * @return if the elements in the two ranges are equal, returns true otherwise, returns false
	 */
	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first, InputIt1 last, InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}

	/**
	 * Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), and false otherwise.
	 * @param first the first range of the elements to compare
	 * @param last the first range of the elements to compare
	 * @param first2 the second range of the elements to compare
	 * @param p binary predicate which returns true if the elements should be treated as equal
	 * @return if the elements in the two ranges are equal, returns true otherwise, returns false
	 */
	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first, InputIt1 last, InputIt2 first2, BinaryPredicate p) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) {
				return false;
			}
		}
		return true;
	}

	/**
	 * Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).
	 * @param first1 the first range of elements to examine
	 * @param last1 the first range of elements to examine
	 * @param first2 the second range of elements to examine
	 * @param last2 the second range of elements to examine
	 * @return true if the first range is lexicographically less than the second
	 */
	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) {
				return true;
			}
			if (*first2 < *first1) {
				return false;
			}
		}
		return (first1 == last1) && (first2 != last2);
	}

	/**
	 * Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).
	 * @param first1 the first range of elements to examine
	 * @param last1 the first range of elements to examine
	 * @param first2 the second range of elements to examine
	 * @param last2 the second range of elements to examine
	 * @param comp comparison function object which returns true if the first argument is less than the second
	 * @return true if the first range is lexicographically less than the second
	 */
	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (comp(*first1, *first2)) {
				return true;
			}
			if (comp(*first2, *first1)) {
				return false;
			}
		}
		return (first1 == last1) && (first2 != last2);
	}

}

#endif //FT_CONTAINERS_ALGORITHM_HPP
