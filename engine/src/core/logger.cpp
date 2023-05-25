#include "logger.hpp"
#include <iostream>
#include <cstdarg>

void FEASY_API feasy::log::_log(Level level, const char *msg, const char *file, i32 line, ...)
{

	const char *level_names[] = {
		"[FATAL:] ",
		"[ERROR:] ",
		"[WARN:] ",
		"[DEBUG:] ",
		"[INFO:] ",
		"[TRACE:] ",
	};

	const char *color_codes[] = {
		"\033[1;31m", // Bold Red (Fatal)
		"\033[0;91m", // Light Red (Error)
		"\033[0;33m", // Yellow (Warn)
		"\033[1;36m", // Cyan (Debug)
		"\033[1;37m", // Bold White (Info)
		"\033[0;37m", // White (Trace)
	};

	// Print log message with color
	std::cout << color_codes[static_cast<i32>(level)] << level_names[static_cast<i32>(level)];

	va_list args;
	va_start(args, line);
	vprintf(msg, args);
	va_end(args);

	std::cout << " file: " << file << " line: " << line;

	// Reset color
	std::cout << "\033[0m" << std::endl;
}
