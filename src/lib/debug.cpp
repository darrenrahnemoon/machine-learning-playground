#pragma once

#include <iostream>
#include <chrono>
#include <string>
#include <map>

namespace debug {

	// Logging
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

	class timer {
		std::string name;
		std::chrono::time_point<std::chrono::high_resolution_clock> start;
		
		public:

			template <typename F, typename... A>
			static void call(const std::string& name, F function, A... args) {
				timer t(name);
				function(args...);
			}

			timer(std::string _name) :
				start(std::chrono::high_resolution_clock::now()),
				name(_name)
			{}

			~timer() {
				this->stop();
			}

			void stop() {
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				log::medium("Timer", this->name, "took", duration.count(), "microseconds");
			}
	};

	// Timing
	std::map<std::string, timer*> timers;
	void startTimer(const std::string& name) {
		timers[name] = new timer(name);
	}
	void stopTimer(const std::string& name) {
		if (timers.contains(name)) {
			timers[name]->stop();
		}
	} 
}