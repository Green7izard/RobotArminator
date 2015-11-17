#include "stdafx.h"
#include "Logger.hpp"

#include <iostream>

namespace RobotArminator
{

    bool Logger::logEnabled = true;
    std::ofstream Logger::fout = std::ofstream();
    const char* Logger::FILE = "logger.log";


    Logger::Logger()
    {
    }


    Logger::~Logger()
    {
    }

    void Logger::disable()
    {
        logEnabled = false;
    }

    void Logger::enable()
    {
        logEnabled = true;
    }

    void Logger::logInfo(char * sender, char * message)
    {
        log(LogLevel::INFO, sender, message);
    }

    void Logger::logWarning(char * sender, char * message)
    {
        log(LogLevel::WARNING, sender, message);
    }

    void Logger::logError(char * sender, char * message)
    {
        log(LogLevel::ERROR, sender, message);
    }

    void Logger::logCritical(char * sender, char * message)
    {
        log(LogLevel::CRITICAL, sender, message);
    }

    void Logger::log(LogLevel level, char * sender, char * message)
    {
        if (logEnabled)
        {
            std::cerr << level << " \t " << sender << " \t " << message << std::endl;
            fout.open(FILE, MODE);
            fout << level << " \t " << sender << " \t " << message << std::endl;
            fout.close();
        }
    }
}