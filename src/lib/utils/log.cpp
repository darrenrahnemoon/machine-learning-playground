#pragma once

#include <iostream>

namespace ML {
	namespace utils {
		namespace log {
			enum Level {
				Low = 0,
				Medium = 1,
				High = 2,
			};

			Level currentLevel = Medium;

			void _log() {}
			template <typename T, typename... Other>
			void _log(T message, Other... otherMessages) {
				std::cout << message;
				if (sizeof...(otherMessages)) {
					std::cout << " ";
					_log(otherMessages...);
				}
				else {
					std::cout << std::endl;
				}
			}

			template <typename... T>
			void low(T... messages) { if (currentLevel <= Low) { _log(messages...); } }

			template <typename... T>
			void medium(T... messages) { if (currentLevel <= Medium) { _log(messages...); } }

			template <typename... T>
			void high(T... messages) { if (currentLevel <= High) { _log(messages...); } }
		}
	}
}