//============================================================================
// Name        : index_sequence.cpp
// Author      : moskvin
// Version     :
// Copyright   : Your copyright notice
// Description : std::index_sequence demo
//============================================================================

/**
 * std::make_index_sequence<N> генерирует тип std::index_sequence<0, 1, ..., N-1>, который представляет собой обычную структуру (с полями size() и value_type).
 * если мы используем эту структуру в качестве параметра некоторой шаблонной функции, то сможем получить доступ к числовой последовательности через
 * пакет параметров шаблона.
 */

#include <iostream>
#include <utility>
#include "tracers.hpp"

// #3
template<std::size_t I0> void print_sequence(std::ostringstream &oss)
{
	oss << I0;
	TRACE(oss);
}

// #2
template<std::size_t I0, std::size_t I1, std::size_t ...I> void print_sequence(std::ostringstream &oss)
{
	oss << I0 << ", ";
	print_sequence<I1, I...>(oss);							// call #2 or #3
}

// #1
template<std::size_t ...I> void print_sequence(std::ostringstream &oss, std::index_sequence<I...>)
{
	print_sequence<I...>(oss);								// call #2 or #3
}


int main() {
	std::ostringstream oss;
	const std::size_t N = 10;								// размер последовательности
	print_sequence(oss, std::make_index_sequence<N>{});		// call #1
	return 0;
}
