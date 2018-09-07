//============================================================================
// Name        : podstruct.cpp
// Author      : moskvin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
// https://habr.com/post/344206/
// https://github.com/apolukhin/magic_get/blob/develop/include/boost/pfr/detail/fields_count.hpp


#include <iostream>
#include <utility>
#include "tracers.hpp"

// fake argument for braced-init-list of user POD-structure
template<std::size_t I> struct ubiq_constructor {
	std::size_t ignore;
	// any-type to any-type cast operator
	// implementation no need
	template<class Type> constexpr operator Type&() const noexcept /* { return (Type&)ignore; } */ ;
};

/**
 * param out выходной параметр, количество полей структуры
 *
 */
template<class T, std::size_t I0, std::size_t ...I>
constexpr auto detect_fields_count(std::size_t &out, std::index_sequence<I0, I...>)
-> decltype (T{ubiq_constructor<I0>{}, ubiq_constructor<I>{}...})
{
	out = sizeof...(I) + 1;
}


template<class T, std::size_t ...I>
constexpr void detect_fields_count(std::size_t &out, std::index_sequence<I...>)
{
	detect_fields_count<T>(out, std::make_index_sequence<sizeof...(I) - 1>{});
}

struct example_struct
{
	int x;
	const char *p;
	double d;
	std::string str;
	unsigned char f1 : 4;
	unsigned char f2:  4;
};

int main() {
	std::ostringstream oss;
	std::size_t out = 0;
	detect_fields_count<example_struct>(out, std::make_index_sequence<sizeof (example_struct)>{});
	oss << "out = " << out;
	TRACE(oss);

	return 0;
}
