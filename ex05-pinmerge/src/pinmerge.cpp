//============================================================================
// Name        : pinmerge.cpp
// Author      : moskvin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

class Test
{

public:
	typedef std::uint8_t pinnum_t;
	typedef std::uint32_t pinmask_t;

	template<typename First, typename... Rest> static pinmask_t PinMerge(pinmask_t pins, First first, Rest... rest)
	{
		pins |= 1 << first;
		return PinMerge(pins, rest...);
	}

	static pinmask_t PinMerge(pinmask_t pins)
	{
		return pins;
	}
};

/*
 * PinMerge<5,4,3,2>(pinnum_t pins) {pins |= 1 << 5; PinMerge<4,3,2>(pins); }
 * PinMerge<4,3,2>(pinnum_t pins) 	{pins |= 1 << 4; PinMerge<3,2>(pins); }
 * PinMerge<3,2>(pinnum_t pins)		{pins |= 1 << 3; PinMerge<2>(pins); }
 * PinMerge<2>(pinnum_t pins)		{pins |= 1 << 2; return pins; }
 */
class Test2
{
public:
	typedef std::uint8_t pinnum_t;
	typedef std::uint32_t pinmask_t;

	template<pinnum_t first, pinnum_t next, pinnum_t... rest>
	static constexpr pinmask_t PinMerge(pinmask_t pins)
	{
		pins |= 1 << first;
		return PinMerge<next, rest...>(pins);
	}

	template<pinnum_t last>
	static constexpr pinmask_t PinMerge(pinmask_t pins)
	{
		return pins |= 1 << last;
	}
};

int main() {
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	Test::pinmask_t pins = 0;

	// Test
	pins = Test::PinMerge(pins, 5, 4, 3, 2);
	std::cout << "Test: pins = 0x" << std::hex << pins << std::endl;

	// Test2 - check for comile-time calculations
	// if it is not a const, - it will be compile error
	static std::uint8_t testArray[Test2::PinMerge<3,2>(0)];
	std::cout << "sizeof testArray: " <<  sizeof testArray << std::endl;



	return 0;
}
