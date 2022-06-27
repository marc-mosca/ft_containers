/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:17:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/06/27 16:16:10 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{

	template<class T1, class T2>
	struct pair
	{
		//	~~	Member types ---------------------------------------------------
		typedef T1	first_type;
		typedef T2	second_type;

		//	~~	Member objects -------------------------------------------------
		first_type	first;
		second_type	second;

		//	~~	Member functions -----------------------------------------------
		pair();
		pair(const T1 &x, const T2 &y);
		template<typename U1, typename U2>
		pair(const pair<U1, U2> &p);
		~pair();
		template<typename U1, typename U2>
		pair<T1, T2> &operator=(const pair<U1, U2> &other);
	};

	//	~~	Constructor --------------------------------------------------------
	template<class T1, class T2>
	pair<T1, T2>::pair(): first(), second()
	{
	}

	template<class T1, class T2>
	pair<T1, T2>::pair(const T1 &x, const T2 &y): first(x), second(y)
	{
	}

	template<class T1, class T2>
	template<typename U1, typename U2>
	pair<T1, T2>::pair(const pair<U1, U2> &p): first(p.first), second(p.second)
	{
	}

	//	~~	Destructor ---------------------------------------------------------
	template<class T1, class T2>
	pair<T1, T2>::~pair()
	{
	}

	//	~~	Operator -----------------------------------------------------------
	template<class T1, class T2>
	template<typename U1, typename U2>
	pair<T1, T2> &pair<T1, T2>::operator=(const pair<U1, U2> &other)
	{
		this->first = other.first;
		this->second = other.second;

		return *this;
	}

	//	~~	Non-member functions -----------------------------------------------
	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return pair<T1, T2>(t, u);
	}

	template<class T1, class T2>
	bool operator==(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template<class T1, class T2>
	bool operator!=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (lhs.first != rhs.first && lhs.second != rhs.second);
	}

	template<class T1, class T2>
	bool operator<(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (lhs.first < rhs.first && lhs.second < rhs.second);
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (lhs.first <= rhs.first && lhs.second <= rhs.second);
	}

	template<class T1, class T2>
	bool operator>(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (lhs.first > rhs.first && lhs.second > rhs.second);
	}

	template<class T1, class T2>
	bool operator>=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (lhs.first >= rhs.first && lhs.second >= rhs.second);
	}

}

#endif // PAIR_HPP
