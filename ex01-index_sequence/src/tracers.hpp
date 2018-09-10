/*
 * tracers.hpp
 *
 *  Created on: 5 сент. 2018 г.
 *      Author: moskw
 */

#ifndef TRACERS_HPP_
#define TRACERS_HPP_

#include <sstream>
#include <iostream>

#define TRACE(oss)	{\
	std::cerr <<"TRACE:"<< __FILE__ << "(" << __FUNCTION__ << "):" << oss.str() << std::endl;\
	oss.str("");\
	oss.clear();\
}



#endif /* TRACERS_HPP_ */
