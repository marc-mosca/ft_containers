/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:25:16 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/07 18:53:52 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_UTILITY_HPP
#define FT_CONTAINERS_UTILITY_HPP

namespace ft {

	/**
	 * ft::pair is a class template that provides a way to store two heterogeneous objects as a single unit. A pair is a specific case of a std::tuple with two elements.
	 * @tparam T1: the types of the elements that the pair stores
	 * @tparam T2: the types of the elements that the pair stores
	 */
	template<class T1, class T2>
	struct pair {
		/**
		 * Member types
		 */
		typedef T1 first_type;
		typedef T2 second_type;

		/**
		 * Member objects
		 */
		T1 first;
		T2 second;

		/**
		 * Default constructor.
		 */
		pair() : first(), second() {}

		/**
		 * Constructor who initialize first with x and second with y.
		 * @param x: the first element to store in the pair
		 * @param y: the second element to store in the pair
		 */
		pair(const T1 &x, const T2 &y) : first(x), second(y) {}

		/**
		 * Constructor who initialize first with p.first and second with p.second.
		 * @param p: the pair to copy into the new pair
		 */
		template<class U1, class U2>
		pair(const ft::pair<U1, U2> &p) : first(p.first), second(p.second) {}

		/**
		 * Destructor.
		 */
		~pair() {}

		/**
		 * Copy assignment operator. Replaces the contents with a copy of the contents of other.
		 * @param other the pair to copy in the current instance
		 * @return the current instance with values of other
		 */
		template<class U1, class U2>
		ft::pair<T1, T2> &operator=(const ft::pair<U1, U2> &other) {
			this->first = other.first;
			this->second = other.second;
			return *this;
		}
	};

	/**
	 * Creates a ft::pair object, deducing the target type from the types of arguments.
	 * @param t the values to construct the pair from
	 * @param u the values to construct the pair from
	 * @return a ft::pair object containing the given values
	 */
	template<typename T1, typename T2>
	ft::pair<T1, T2> make_pair(T1 t, T2 u) {
		return ft::pair<T1, T2>(t, u);
	}

	/**
	 * Tests if both elements of lhs and rhs are equal, that is, compares lhs.first with rhs.first and lhs.second with rhs.second.
	 * @param lhs pairs to compare
	 * @param rhs pairs to compare
	 * @return true if both lhs.first == rhs.first and lhs.second == rhs.second, otherwise false
	 */
	template<class T1, class T2>
	bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	/**
	 * Tests if both elements of lhs and rhs are equal, that is, compares lhs.first with rhs.first and lhs.second with rhs.second.
	 * @param lhs pairs to compare
	 * @param rhs pairs to compare
	 * @return true if both lhs.first != rhs.first and lhs.second != rhs.second, otherwise false
	 */
	template<class T1, class T2>
	bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
		return lhs.first != rhs.first && lhs.second != rhs.second;
	}

	/**
	 * Compares lhs and rhs lexicographically by operator>, that is, compares the first elements and only if they are equivalent, compares the second elements.
	 * @param lhs pairs to compare
	 * @param rhs pairs to compare
	 * @return true if both lhs.first > rhs.first and lhs.second > rhs.second, otherwise false
	 */
	template<class T1, class T2>
	bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
		return lhs.first > rhs.first && lhs.second > rhs.second;
	}

	/**
	 * Compares lhs and rhs lexicographically by operator>=, that is, compares the first elements and only if they are equivalent, compares the second elements.
	 * @param lhs pairs to compare
	 * @param rhs pairs to compare
	 * @return true if both lhs.first >= rhs.first and lhs.second >= rhs.second, otherwise false
	 */
	template<class T1, class T2>
	bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
		return lhs.first >= rhs.first && lhs.second >= rhs.second;
	}

	/**
	 * Compares lhs and rhs lexicographically by operator<, that is, compares the first elements and only if they are equivalent, compares the second elements.
	 * @param lhs pairs to compare
	 * @param rhs pairs to compare
	 * @return true if both lhs.first < rhs.first and lhs.second < rhs.second, otherwise false
	 */
	template<class T1, class T2>
	bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
		return lhs.first < rhs.first && lhs.second < rhs.second;
	}

	/**
	 * Compares lhs and rhs lexicographically by operator<=, that is, compares the first elements and only if they are equivalent, compares the second elements.
	 * @param lhs pairs to compare
	 * @param rhs pairs to compare
	 * @return true if both lhs.first <= rhs.first and lhs.second <= rhs.second, otherwise false
	 */
	template<class T1, class T2>
	bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
		return lhs.first <= rhs.first && lhs.second <= rhs.second;
	}

}

#endif //FT_CONTAINERS_UTILITY_HPP
