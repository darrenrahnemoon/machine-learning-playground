#pragma once

#include <string>

#include "lib/utils/debug.cpp"

namespace ML {
	namespace file {
		FILE* open(const std::string& path) {
			using namespace std::string_literals;
			debug::timer timer("Opening file: "s + path);
			FILE* file = fopen(path.c_str(), "rb");
			if (!file) {
				throw std::runtime_error("Cannot read file:"s + path);
			}
			return file;
		}
	}
}