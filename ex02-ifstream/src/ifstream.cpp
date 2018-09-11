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
 * workaround: #define _GLIBCXX_USE_CXX11_ABI 0
 */

#include <fstream>
#include "tracers.hpp"

void print_stream_flags(std::ostringstream &oss, const std::ifstream &ifs)
{
	oss << std::boolalpha << "(failbit=" << ifs.fail() << ", eofbit=" << ifs.eof() << ", badbit=" << ifs.bad() << ")";
}

int main() {
	std::ostringstream oss;
	const std::string filename("M:\\git\\cpp-tutors\\ex02-ifstream\\Debug\\82574L.EEP");
	std::ifstream ifs;

	// all exceptions are enabled
	ifs.exceptions(std::ios_base::failbit | std::ios_base::eofbit | std::ios_base::badbit);

	try
	{
		ifs.open(filename, std::ios_base::binary);
		if (ifs.is_open())
		{
			for(;;)
			{
				ifs.get(*oss.rdbuf());
				oss << " (total: " << ifs.gcount() << " characters )";
				TRACE_BY_STREAM(oss);
				ifs.seekg(1, std::ios_base::cur);	// ignore '\n' symbol
			}
		}
	} catch (const /* std::ios_base::failure */ std::exception &e) {
		oss << "WTF?! " << e.what();
		print_stream_flags(oss, ifs);
		TRACE_BY_STREAM(oss);
	}
	return 0;
}
