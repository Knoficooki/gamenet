#pragma once
#include <exception>
#include <stdint.h>

#ifndef NET_EXCEPTION_INCLUDE
#define NET_EXCEPTION_INCLUDE
#define netexcept(msg, level) net::exception(msg, level, __LINE__, __FILE__, __func__)
#endif

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

#ifdef NET_EXCEPTION_IMPLEMENTATION
// exception.cpp
#include <string>
#include <fstream>
#include <iostream>

void net::exception::handle(void)
{
	if (except_level > net::exception::log_level) {
		log();
	}
#ifdef _DEBUG
	if (except_level > net::exception::out_level) {
		std::cerr << what() << std::endl;
	}
#endif
}

const char* net::exception::what()
{
	std::string msg = message;
	msg += "\n\tLine: ";
	msg += std::to_string(line);
	msg += "\n\tFile: ";
	msg += file;
	if (function) {
		msg += "\n\tFunction: ";
		msg += function;
	}
	const char* res = strdup(msg.c_str());
	return res;
}

net::exception::exception(const char* msg, level lvl,uint64_t line, const char* file, const char* func)
	: line(line), file(file), function(func), message(msg), except_level(lvl)
{
	static bool setup = false;
	if (!setup) {
		setup = true;
	}
}

const char* net::exception::level_string(level lvl)
{
	switch (lvl)
	{
	case level::none:
		return "none";
	case level::info:
		return "Info";
	case level::warning:
		return "Warning";
	case level::error:
		return "ERROR";
	case level::fatal:
		return "FATAL";
	default:
		return "";
	}
}

void net::exception::log() {
	static std::ofstream logger("networking.log", std::ios::out);
	logger << "Level: " << level_string(except_level) << " (" << (uint8_t)except_level << ")\n" << what() << std::endl;
}

#undef NET_EXCEPTION_IMPLEMENTATION
#endif // NET_EXCEPTION_IMPLEMENTATION

