/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:51:41 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/05 11:51:48 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_UTILITY_HPP
#define FT_CONTAINERS_UTILITY_HPP

namespace ft {

	//	~~	PAIR ---------------------------------------------------------------

	template<class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second() {}
		pair(const T1 &x, const T2 &y) : first(x), second(y) {}
		template<class U1, class U2>
		pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}
		~pair() {}
		template<class U1, class U2>
		pair<T1, T2> &operator=(const pair<U1, U2> &other) {
			this->first = other.first;
			this->second = other.second;
			return *this;
		}
	};

	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1 t, T2 u) {
		return pair<T1, T2>(t, u);
	}

	template<typename T1, typename T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
	template<typename T1, typename T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first != rhs.first && lhs.second != rhs.second;
	}
	template<typename T1, typename T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first < rhs.first && lhs.second < rhs.second;
	}
	template<typename T1, typename T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first <= rhs.first && lhs.second <= rhs.second;
	}
	template<typename T1, typename T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first > rhs.first && lhs.second > rhs.second;
	}
	template<typename T1, typename T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first >= rhs.first && lhs.second >= rhs.second;
	}

}

#endif //FT_CONTAINERS_UTILITY_HPP
