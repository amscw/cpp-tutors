/*
 * tracers.hpp
 *
 *  Created on: 5 сент. 2018 г.
 *      Author: moskvin
 */

#ifndef TRACERS_HPP_
#define TRACERS_HPP_

#include <sstream>
#include <iostream>

#define TRACE_BY_STREAM(oss)	{\
	std::cerr <<"TRACE:"<< __FILE__ << "(" << __FUNCTION__ << "):" << oss.str() << std::endl;\
	oss.str("");\
	oss.clear();\
}

#define TRACE_BY_PRINTF(fmt,args...) {\
	printf("%s(%s)-"fmt"\n", __FILE__, __FUNCTION__, ##args);\
	fflush(stdout);\
}

#endif /* TRACERS_HPP_ */
