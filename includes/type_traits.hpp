#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{
	/* ft::enable_if */

	template <bool T, class U = void>
	struct enable_if
	{};
	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	/* ft::remove_cv */

	template <class T>
	struct remove_cv
	{
		typedef T type;
	};
	template <class T>
	struct remove_cv<T const>
	{
		typedef T type;
	};
	template <class T>
	struct remove_cv<T volatile>
	{
		typedef T type;
	};
	template <class T>
	struct remove_cv<T const volatile>
	{
		typedef T type;
	};

	/* ft::remove_const */

	template <class T>
	struct remove_const
	{
		typedef T type;
	};
	template <class T>
	struct remove_const<const T>
	{
		typedef T type;
	};

	/* ft::remove_volatile */

	template <class T>
	struct remove_volatile
	{
		typedef T type;
	};
	template <class T>
	struct remove_volatile<T volatile>
	{
		typedef T type;
	};

	/* ft::remove_pointer */
	template <class T>
	struct remove_pointer
	{
		typedef T type;
	};
	template <class T>
	struct remove_pointer<T *>
	{
		typedef T type;
	};

	/* ft::integral_constant */

	template< class T, bool v>
	struct integral_constant
	{
		enum {value = v};
		typedef T	value_type;
		typedef integral_constant<T, v> type;
		operator value_type( void ) const { return value; }
	};
	template<>
	struct integral_constant<bool, true>
	{
		enum {value = true};
		typedef bool	value_type;
		typedef integral_constant<bool, true> type;
		operator value_type( void ) const { return value; }
	};
	template<>
	struct integral_constant<bool, false>
	{
		enum {value = false};
		typedef bool	value_type;
		typedef integral_constant<bool, false> type;
		operator value_type( void ) const { return value; }
	};

	/* truth_type */

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <bool>
	struct truth_type
	{
		typedef false_type type;
	};
	template <>
	struct truth_type<true>
	{
		typedef true_type type;
	};

	/* is_constt */

	template <class T>
	struct is_const : public false_type
	{};
	template <class T>
	struct is_const<const T> : public true_type
	{};

	/* is_same */

	template<class T, class U>
	struct is_same : false_type 
	{
		enum {value = false};
	};
	template<class T>
	struct is_same<T, T> : true_type 
	{
		enum {value = true};
	};

	/* is_integral */

	template <class T>
	struct is_integral						: integral_constant<T, false>
	{};
	template <class T>
	struct is_integral<T const> 			: integral_constant<T, is_integral<T>::value>
	{};
	template <class T>
	struct is_integral<T volatile>			: integral_constant<T, is_integral<T>::value>
	{};
	template <class T>
	struct is_integral<T const volatile>	: integral_constant<T, is_integral<T>::value>
	{};

	template <>
	struct is_integral<signed int>			: integral_constant<signed int, true>
	{};
	template <>
	struct is_integral<unsigned int>		: integral_constant<unsigned int, true>
	{};
	template <>
	struct is_integral<char>				: integral_constant<char, true>
	{};
	template <>
	struct is_integral<signed char>			: integral_constant<signed char, true>
	{};
	template <>
	struct is_integral<unsigned char>		: integral_constant<unsigned char, true>
	{};
	template <>
	struct is_integral<wchar_t>				: integral_constant<wchar_t, true>
	{};
	template <>
	struct is_integral<short>				: integral_constant<short, true>
	{};
	template <>
	struct is_integral<unsigned short>		: integral_constant<unsigned short, true>
	{};
	template <>
	struct is_integral<long>				: integral_constant<long, true>
	{};
	template <>
	struct is_integral<unsigned long>		: integral_constant<unsigned long, true>
	{};
	template <>
	struct is_integral<long long>			: integral_constant<long long, true>
	{};
	template <>
	struct is_integral<unsigned long long>	: integral_constant<unsigned long long, true>
	{};
}

#endif
