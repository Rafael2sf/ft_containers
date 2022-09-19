#pragma once

namespace ft
{
	template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 __first1, InputIt1 __last1, InputIt2 __first2 )
	{
		while (__first1 != __last1)
		{
			if (*__first1++ != *__first2++)
				return false;
		}
		return true;
	}

	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 __first1, InputIt1 __last1, 
		InputIt2 __first2, BinaryPredicate __bp )
	{
		while (__first1 != __last1)
		{
			if (!__bp(*__first1++ != *__first2++))
				return false;
		}
		return true;
	}

	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare(
		InputIt1 __first1, InputIt1 __last1,
		InputIt2 __first2, InputIt2 __last2 )
	{
		while ((__first1 != __last1) && (__first2 != __last2))
		{
			if (*__first1 < *__first2)
				return true;
			else if (*__first2 < *__first1)
				return false;
			__first1++;
			__first2++;
		}
		return (__first1 == __last1) && (__first2 != __last2);
	}

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare(
		InputIt1 __first1, InputIt1 __last1,
		InputIt2 __first2, InputIt2 __last2,
		Compare __comp )
	{
		while ((__first1 != __last1) && (__first2 != __last2))
		{
			if (__comp(*__first1, *__first2))
				return true;
			else if (__comp(*__first2, *__first1))
				return false;
		}
		return (__first1 == __last1) && (__first2 != __last2);
	}
}
