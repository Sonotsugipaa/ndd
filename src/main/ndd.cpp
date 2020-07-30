#include <iostream>
#include <ndd/baseconvert.hpp>







int main(int argn, char** args) {
	if(argn < 2) {
		std::cerr
			<< "Usage:\n   "
			<< args[0] << " [from=<radix>] [to=<radix>] <number>...\n"
			   "\n"
			   "<number>:\n"
			   "   A reasonably small integer number.\n"
			   "   The number can have the following radix prefixes:\n"
			   "   0b for radix 2; 0 for radix 8; 0d for radix 10;\n"
			   "   0x for radix 16.\n"
			   "   Using a prefix overrides the closest 'from' argument to the left,\n"
			   "   while using no prefix will not override it.\n"
			   "\n"
			   "[from=<radix>]:\n"
			   "   The radix to convert the remaining numbers from, preceded by \"from=\".\n"
			   "\n"
			   "[to=<radix>]:\n"
			   "   The radix to convert the remaining numbers to, preceded by \"to=\".\n"
			   "\n"
			   "There can be any number of arguments after the first one;\n"
			   "the arguments can be provided in any order, although the arguments\n"
			   "order affects the numbers that will be printed.\n"
			   "\n"
			   "If any argument fails to be parsed, the program's exit code indicates\n"
			   "a failure, but all valid arguments will still be processed and\n"
			   "output will be redirected from stdout to stderr.\n";
		return EXIT_FAILURE;
	}
	return ndd::run(args+1)? EXIT_SUCCESS : EXIT_FAILURE;
}
