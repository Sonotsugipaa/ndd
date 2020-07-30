#include <iostream>

#include "ndd/baseconvert_templates.hpp"



namespace {


	bool process_arg(
			const std::string& arg,
			unsigned& radix_src, unsigned& radix_dest,
			std::ostream& out
	) {
		unsigned number;
		bool success = false;
		if(arg.starts_with("from=")) {
			success = ndd::parse(arg.substr(5), &number);
			success = success && number > 1 && number <= ndd::MAX_RADIX;
			if(success)  radix_src = number;
		} else
		if(arg.starts_with("to=")) {
			success = ndd::parse(arg.substr(3), &number);
			success = success && number > 1 && number <= ndd::MAX_RADIX;
			if(success)  radix_dest = number;
		} else {
			unsigned radix_length;
			unsigned radix = ndd::parse_prefix(arg, &radix_length);
			if(radix_length == 0)  radix = radix_src;
			if(! ndd::parse(arg.substr(radix_length), &number, radix)) {
				return false; }
			std::string str_out = ndd::to_string(number, radix_dest);
			if(! str_out.empty()) {
				out << str_out << std::endl;
				return true;
			}
		}
		return success;
	}

}



namespace ndd {

	bool run(char** args) {
		std::string arg = *args;
		unsigned radix_src = 10;
		unsigned radix_dest = 10;
		bool success;
		if(*args != nullptr) {
			success = ::process_arg(
				arg, radix_src, radix_dest, success? std::cout : std::cerr);
			++args;
		}
		while(*args != nullptr) {
			arg = *args;
			success =
				::process_arg(
					arg, radix_src, radix_dest, success? std::cout : std::cerr
				) && success;
			++args;
		}
		return success;
	}

}