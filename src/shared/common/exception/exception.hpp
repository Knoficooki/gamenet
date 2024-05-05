#pragma once

#include <exception>

namespace net {
	class exception : private std::exception {
	public:
		enum class level {
			none = 0,
			info,
			warning,
			error,
			fatal,
		};
		void handle(void);
		const char* what();
		exception(const char*, level, uint64_t, const char*, const char* = nullptr);
		constexpr static level log_level = level::warning;
		constexpr static level out_level = level::error;
	private:
		unsigned long long line;
		const char* file;
		const char* function;
		const char* message;
		level except_level;

		static const char* level_string(level);

		void log();
	};
}
