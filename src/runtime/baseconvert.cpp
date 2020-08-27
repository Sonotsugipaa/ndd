#include <iostream>

#include "ndd/baseconvert_templates.hpp"



namespace {


	bool process_arg(
			const std::string& arg,
			unsigned& radix_src, unsigned& radix_dest,
			std::ostream& out
	) {
		using num_t = int64_t;
		num_t number;
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
			bool neg;
			unsigned radix = ndd::parse_prefix(arg, &radix_length, &neg);
			if(radix_length == 0)  radix = radix_src;
			std::string arg_no_prefix = arg.substr(radix_length);
			std::string str_out;
			if(arg[0] == '-') {
				str_out = "-";
			}
			if(! ndd::parse<num_t, std::string, false>(
				arg_no_prefix, &number, radix)
			) {
				return false;
			}
			str_out += ndd::to_string(number, radix_dest);
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
		bool success = true;
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
