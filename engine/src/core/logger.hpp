#pragma once

#include "feasy.hpp"

namespace feasy
{
	namespace log
	{
		enum class Level
		{
			fatal = 0,
			error = 1,
			warn = 2,
			debug = 3,
			info = 4,
			trace = 5
		};

		void FEASY_API _log(Level level, const char *msg, const char *file, i32 line, ...);
	}
}
#define FEASY_LOG_FATAL(msg, ...) feasy::log::_log(feasy::log::Level::fatal, msg, __FILE__, __LINE__, ##__VA_ARGS__)
#define FEASY_LOG_ERROR(msg, ...) feasy::log::_log(feasy::log::Level::error, msg, __FILE__, __LINE__, ##__VA_ARGS__)
#define FEASY_LOG_WARN(msg, ...) feasy::log::_log(feasy::log::Level::warn, msg, __FILE__, __LINE__, ##__VA_ARGS__)
#ifdef DEBUG
#define FEASY_LOG_DEBUG(msg, ...) feasy::log::_log(feasy::log::Level::debug, msg, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define FEASY_LOG_DEBUG(msg, ...)
#endif
#define FEASY_LOG_INFO(msg, ...) feasy::log::_log(feasy::log::Level::info, msg, __FILE__, __LINE__, ##__VA_ARGS__)
#define FEASY_LOG_TRACE(msg, ...) feasy::log::_log(feasy::log::Level::trace, msg, __FILE__, __LINE__, ##__VA_ARGS__)
