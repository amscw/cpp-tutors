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
#include <regex>
#include <vector>
#include "tracers.hpp"

void print_stream_flags(std::ostringstream &oss, const std::ifstream &ifs)
{
	oss << std::boolalpha << "(failbit=" << ifs.fail() << ", eofbit=" << ifs.eof() << ", badbit=" << ifs.bad() << ")";
}

int main() {
	std::ostringstream oss;
	const std::string filename("M:\\git\\cpp-tutors\\ex02-ifstream\\Debug\\82574L.EEP");
	std::ifstream ifs;
	std::vector<std::uint16_t> v;

	// all exceptions are enabled
	ifs.exceptions(std::ios_base::failbit | std::ios_base::eofbit | std::ios_base::badbit);

	try
	{
		ifs.open(filename, std::ios_base::binary);
		if (ifs.is_open())
		{
			for(std::string str;;)
			{
				// get line
				ifs.get(*oss.rdbuf());
				str = std::move(oss.str());

				// parse line
				std::smatch sm;
				while(std::regex_search(str, sm, std::regex{"[0-9a-fA-F]+"}))
			    {
			        // std::cout << sm.str() << std::endl;
					v.push_back(std::stoul(sm.str(), nullptr, 16));
			        str = sm.suffix();
			    }

				// do next
				oss.str("");
				oss.clear();
				ifs.seekg(1, std::ios_base::cur);	// ignore '\n' symbol
			}
		}
	} catch (const /* std::ios_base::failure */ std::exception &e) {
		oss << "WTF?! " << e.what();
		print_stream_flags(oss, ifs);
		TRACE_BY_STREAM(oss);
	}
	oss << "found: " << v.size() << " regs";
	TRACE_BY_STREAM(oss);
	return 0;
}
