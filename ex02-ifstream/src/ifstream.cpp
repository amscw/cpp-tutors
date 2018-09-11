//============================================================================
// Name        : ofstream.cpp
// Author      : moskvin
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

/**
 * WARNING! Не можем перехватывать std::ios_base::failure, см:
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66145
 */

#include <fstream>
#include <vector>
#include <exception>
#include "tracers.hpp"

int main() {
	const std::string filename{"82574L.EEP"};
	std::ifstream ifs;
	std::vector<std::uint32_t> raw;

	// all exceptions are enabled
	ifs.exceptions(std::ios_base::failbit | std::ios_base::eofbit | std::ios_base::badbit);

	try
	{
		std::uint32_t tmp;
		ifs.open(filename, std::ios_base::binary);
		for (;;) ifs.read(reinterpret_cast<char*>(&tmp), sizeof tmp);
	} catch (const std::exception &e) {
		std::ostringstream oss;
		oss << "WTF?! " << e.what();
		TRACE_BY_STREAM(oss);
	}
	return 0;
}
