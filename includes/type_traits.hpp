#pragma once

namespace ft
{
	/* ft::enable_if */
	template <bool T, class U = void> struct enable_if {};
	template <class T> struct enable_if<true, T> { typedef T type; };

	/* ft::remove_cv */

	template <class T> struct remove_cv						{typedef T type;};
	template <class T> struct remove_cv<T const>			{typedef T type;};
	template <class T> struct remove_cv<T volatile>			{typedef T type;};
	template <class T> struct remove_cv<T const volatile>	{typedef T type;};

	/* ft::remove_const */

	template <class T> struct remove_const					{typedef T type;};
	template <class T> struct remove_const<T const>			{typedef T type;};

	/* ft::remove_volatile */

	template <class T> struct remove_volatile				{typedef T type;};
	template <class T> struct remove_volatile<T volatile>	{typedef T type;};

	/* ft::is_integral */

	template <class T> struct is_integral {
		enum {value = false};
		operator bool() const { return (value); }
	};
	template <class T>
	struct is_integral<T const> {
		enum {value = is_integral<T>::value};
		operator bool() const { return (value); }
	};
	template <class T>
	struct is_integral<T volatile> {
		enum {value = is_integral<T>::value};
		operator bool() const { return (value); }
	};
	template <class T>
	struct is_integral<T const volatile> {
		enum {value = is_integral<T>::value};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<signed int> {
		enum {value = true};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<unsigned int> {
		enum {value = true};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<signed char> {
		enum {value = true};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<unsigned char> {
		enum {value = true};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<bool> {
		enum {value = true};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<wchar_t> {
		enum {value = true};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<short> {
		enum {value = true};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<unsigned short> {
		enum {value = true};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<long> {
		enum {value = true};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<unsigned long> {
		enum {value = true};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<long long> {
		enum {value = true};
		operator bool() const { return (value); }
	};
	template <> struct is_integral<unsigned long long> {
		enum {value = true};
		operator bool() const { return (value); }
	};
}
