#include "logger.hpp"

// #include <ctime>

// using namespace feasy;

// void feasy::Logger::initialize(LogLevel level)
// {
// 	if (instance != nullptr)
// 		return;

// 	instance = new Logger();
// 	instance->m_level = level;
// 	instance->m_file.open("log.txt", std::ofstream | std::ofstream app);
// }

// void feasy::Logger::shutdown()
// {
// 	delete instance;
// 	instance = nullptr;
// }

// Logger &feasy::Logger::operator<<(std::ostream &(*func)(std::ostream &))
// {
// 	func(m_file);
// 	func(std::cout);
// 	return *this;
// }

// void feasy::shutdown()
// {
// 	instance->m_file.close();
// 	delete instance;
// 	instance = nullptr;
// }

// void Logger::log(LogLevel msgLevel, const String &message, const char *file, int line)
// {
// 	if (msgLevel <= logLevel)
// 	{
// 		// Aktuelles Datum und Uhrzeit abrufen
// 		std::time_t now = std::time(nullptr);
// 		std::string timestamp = std::ctime(&now);

// 		// Entferne das abschließende Zeilenumbruchzeichen von der Zeitstempelzeichenkette
// 		timestamp.pop_back();

// 		// Erstelle eine Log-Nachricht und füge sie zur Liste hinzu
// 		LogMessage logMsg{msgLevel, "[" + timestamp + "] " +
// 										"[" + logLevelToString(msgLevel) + "] " +
// 										"[" + file + ":" + std::to_string(line) + "] " +
// 										message};
// 		logList.push_front(logMsg);

// 		// Schreibe die Log-Nachricht in die Log-Datei
// 		logFile << logMsg.message << std::endl;

// 		// Gib die Log-Nachricht auch auf der Konsole aus
// 		printLogMessage(logMsg);
// 	}
// }

// String Logger::logLevelToString(LogLevel level)
// {
// 	{
// 		switch (level)
// 		{
// 		case LogLevel::FATAL:
// 			return "FATAL";
// 		case LogLevel::ERROR:
// 			return "ERROR";
// 		case LogLevel::WARN:
// 			return "WARN";
// 		case LogLevel::INFO:
// 			return "INFO";
// 		case LogLevel::DEBUG:
// 			return "DEBUG";
// 		case LogLevel::TRACE:
// 			return "TRACE";
// 		default:
// 			return "UNKNOWN";
// 		}
// 	}
// }

// void feasy::Logger::printLogMessage(const LogMessage &logMsg)
// {
// 	// Farben für die verschiedenen Log-Level festlegen
// 	const String COLOR_RESET = "\033[0m";
// 	const String COLOR_RED = "\033[1;31m";
// 	const String COLOR_YELLOW = "\033[1;33m";
// 	const String COLOR_CYAN = "\033[1;36m";

// 	// Farbe je nach Log-Level festlegen
// 	std::string color;
// 	switch (logMsg.level)
// 	{
// 	case LogLevel::FATAL:
// 		color = COLOR_RED;
// 		break;
// 	case LogLevel::ERROR:
// 		color = COLOR_RED;
// 		break;
// 	case LogLevel::WARN:
// 		color = COLOR_YELLOW;
// 		break;
// 	case LogLevel::INFO:
// 		color = COLOR_RESET;
// 		break;
// 	case LogLevel::DEBUG:
// 		color = COLOR_CYAN;
// 		break;
// 	case LogLevel::TRACE:
// 		color = COLOR_RESET;
// 		break;
// 	default:
// 		color = COLOR_RESET;
// 		break;
// 	}

// 	// Log-Nachricht mit Farbe ausgeben
// 	std::cout << color << logMsg.message << COLOR_RESET << std::endl;
// }
