#pragma once

namespace ML {
	namespace utils {
		template <typename T>
		void swapEndian(T &value) {
			union U {
				T value;
				std::array<uint8_t, sizeof(T)> raw;
			} src, dst;

			src.value = value;
			std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
			value = dst.value;
		}
	}
}