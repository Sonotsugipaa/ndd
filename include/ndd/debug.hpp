#pragma once



#ifndef NDEBUG
	#include <iostream>
	namespace ndd {
		constexpr std::ostream& debug_out = std::cerr;
	}
#endif