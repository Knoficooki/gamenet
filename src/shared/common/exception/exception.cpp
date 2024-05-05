#include "exception.hpp"
#include <string>
#include <fstream>
#include <iostream>

void net::exception::handle(void)
{
	if (except_level > net::exception::log_level) {
		log();
	}
	if (except_level > net::exception::out_level) {
		std::cerr << what() << std::endl;
	}
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