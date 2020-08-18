#pragma once

#include <string>
#include <cstdint>

#include "debug.hpp"



namespace ndd {

	constexpr unsigned MAX_RADIX = 11 + 'z' - 'a';


	/* Returns the detected radix, or 10 if the given string doesn't
	 * have a prefix; the result is undefined if the string is empty or
	 * an invalid number representation.
	 * If radix_length is not nullptr, then the length of the prefix is
	 * written into *radix_length.
	 *
	 * Supported radix patterns:
	 *  -  0b* = radix 2
	 *  -  0B* = radix 2
	 *  -  0* = radix 8
	 *  -  0o* = radix 8
	 *  -  0d* = radix 10 (unusual)
	 *  -  0D* = radix 10 (unusual)
	 *  -  0x* = radix 16
	 *  -  0X* = radix 16 */

	template<typename str_t>
	unsigned parse_prefix(const str_t str, unsigned* radix_length = nullptr) {
		unsigned sign = (str[0] == '-' || str[0] == '+')? 1 : 0;
		if(radix_length != nullptr)  *radix_length = 0;
		char c = str[0+sign];
		if(c == '0') {
			if(radix_length != nullptr)  *radix_length = 2+sign;
			c = str[1+sign];
			if(c == 'x' || c == 'X') {
				return 16;
			} else if(c == 'b' || c == 'B') {
				return 2;
			} else if(c == 'd' || c == 'D') {
				return 10;
			} else if(c == 'o' || c == 'O') {
				return 8;
			} else {
				if(radix_length != nullptr)  *radix_length = 1+sign;
				return 8;
			}
		} else {
			return 10;
		}
	}


	/* Attempts to map a numerical value to a digit, according to the
	 * [0-9a-b] set of characters (or the [0-9A-B] one).
	 *
	 * If the operation succeeds, the digit's numerical value is returned;
	 * if the operation fails, returns -1. */

	template<typename char_t>
	int char_to_digit(char_t character) {
		if(character >= '0' && character <= '9') {
			return character - '0';
		} else
		if(character >= 'a' && character <= 'z') {
			return 10 + (character - 'a');
		} else
		if(character >= 'A' && character <= 'Z') {
			return 10 + (character - 'A');
		}
		return -1;
	}


	/* Attempts to map a digit to a numerical value, according to the
	 * [0-9a-b] set of characters (or the [0-9A-B] one).
	 *
	 * If the operation succeeds, the number's digit is returned;
	 * if the operation fails, returns '\0'. */

	template<typename int_t, bool upper_case = false>
	char digit_to_char(int_t digit) {
		if(digit >= 0 && digit <= 9) {
			return digit + '0';
		} else
		if(digit >= 10 && digit <= MAX_RADIX) {
			if constexpr(upper_case) {
				return digit + 'A' - 10;
			} else {
				return digit + 'a' - 10;
			}
		} else {
			return '\0';
		}
	}


	/* Creates a string with the representation of the given number with
	 * the given radix.
	 *
	 * If the radix exceeds ndd::MAX_RADIX, "" is returned. */

	template<typename int_t>
	std::string to_string(int_t x, unsigned radix) {
		if(radix > MAX_RADIX)  return "";
		std::string str;
		bool neg = x < 0;
		if(neg)  str = "-";
		while(x != 0) {
			str.push_back(digit_to_char(x % radix));
			x /= radix;
		}
		// the digits have to be reversed
		unsigned swap_until = str.length() / 2;
		for(unsigned i=0; i < swap_until; ++i) {
			if(i != ((str.length() - i) - 1)) {
				std::swap(str[i], str[(str.length() - i) - 1]);
			}
		}
		return str;
	}


	/* Attempts to parse the string as a number with a guessed radix
	 * (see the parse_prefix function, defined in this header).
	 *
	 * If the operation fails, the function returns false;
	 * if the operation succeeds, the parsed number is written to
	 * *destination (unless *destination == nullptr) and the function
	 * returns true. */

	template<typename int_t, typename str_t>
	bool parse(const str_t x, int_t* destination) {
		unsigned i;
		unsigned radix = parse_prefix(x, &i);
		if(radix == 0)  radix = 10;
		bool neg = x[0] == '-' || x[0] == '+';
		int digit;
		*destination = 0;
		while(x[i] != '\0') {
			digit = char_to_digit(x[i]);
			if(digit < 0 || digit > radix) {
				return false; }
			*destination = (*destination * radix) + digit;
			++i;
		}
		return true;
	}


	/* Attempts to parse the string as a number with the given radix;
	 * the string parameter must not contain a radix prefix.
	 *
	 * If the operation fails, the function returns false, and *destination
	 * holds an incompletely parsed number (up to an invalid character);
	 * if the operation succeeds, the parsed number is written to
	 * *destination (unless *destination == nullptr) and the function
	 * returns true. */

	template<typename int_t, typename str_t>
	bool parse(const str_t x, int_t* destination, unsigned radix, char delim = '\0') {
		unsigned i = 0;
		int digit;
		*destination = 0;
		while(x[i] != delim) {
			digit = char_to_digit(x[i]);
			if(digit < 0 || digit > radix) {
				return false; }
			*destination = (*destination * radix) + digit;
			++i;
		}
		return true;
	}

}