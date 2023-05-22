#pragma once

// #include "feasy.hpp"

// #include "containers/feasy_string.hpp"
// #include "core/ref.hpp"

// #include <iostream>
// #include <fstream>

// namespace feasy
// {
//     enum class LogLevel
//     {
//         FATAL,
//         ERROR,
//         WARN,
//         INFO,
//         DEBUG,
//         TRACE
//     };

//     class FEASY_API Logger
//     {
//     public:
//         static Logger *instance{nullptr};

//         static void initialize(LogLevel level);
//         static void shutdown();

//         template <typename T>
//         Logger &operator<<(const T &value)
//         {
//             m_file << value;
//             std::cout << value;
//             return *this;
//         }

//         Logger &operator<<(std::ostream &(*func)(std::ostream &));

//         template <typename... Args>
//         void logf(LogLevel msgLevel, const char *file, int line, const char *format, Args &&...args)
//         {
//             if (msgLevel <= logLevel)
//             {
//                 constexpr int MAX_BUFFER_SIZE = 512;
//                 char buffer[MAX_BUFFER_SIZE];

//                 int ret = std::snprintf(buffer, MAX_BUFFER_SIZE, format, std::forward<Args>(args)...);

//                 if (ret >= 0 && ret < MAX_BUFFER_SIZE)
//                 {
//                     log(msgLevel, buffer, file, line);
//                 }
//                 else
//                 {
//                     log(LogLevel::ERROR, "Error formatting log message", __FILE__, __LINE__);
//                 }
//             }
//         }

//     private:
//         std::ofstream m_file;
//         LogLevel m_level;

//         String logLevelToString(LogLevel level);
//         void printLogMessage(const LogMessage &logMsg);
//     };

// // #define FEASY_LOG(logger, level, message) logger::instance->log(level, message, __FILE__, __LINE__)
// #define FEASY_FATAL(message, ...) logger::instance->logf(LogLevel::FATAL, __FILE__, __LINE__, message, __VA_ARGS__)
// #define FEASY_ERROR(message, ...) logger::instance->logf(LogLevel::ERROR, __FILE__, __LINE__, message, __VA_ARGS__)
// #define FEASY_INFO(message, ...) logger::instance->logf(LogLevel::INFO, __FILE__, __LINE__, message, __VA_ARGS__)

// #ifdef DEBUG
// #define FEASY_DEBUG(message, ...) logger::instance->logf(LogLevel::DEBUG, __FILE__, __LINE__, message, __VA_ARGS__)
// #else

// #define FEASY_DEBUG(message, ...) ()
// #define FEASY_TRACE(message, ...) logger::instance->logf(LogLevel::TRACE, __FILE__, __LINE__, message, __VA_ARGS__)

// }