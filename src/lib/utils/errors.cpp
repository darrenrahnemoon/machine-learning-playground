#pragma once

#include <stdexcept>
namespace ML {
	namespace errors {
		class NotImplemented : public std::runtime_error {
			public:
				NotImplemented() : std::runtime_error("Not Implemented.") {}
		};
	}
}