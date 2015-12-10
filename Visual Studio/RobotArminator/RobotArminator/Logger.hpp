#pragma once
#include "stdafx.h"
#include <fstream>

namespace RobotArminator
{

    class Logger
    {
    public:
        enum LogLevel
        {
            INFO = 0,
            WARNING = 1,
            ERROR = 2,
            CRITICAL = 3
        };

        ~Logger();
        static void disable();
        static void enable();

        static void logInfo(char* sender, char* message);
        static void logWarning(char* sender, char* message);
        static void logError(char* sender, char* message);
        static void logCritical(char* sender, char* message);
        static void log(LogLevel level, char* sender, char* message);
    private:
        Logger();
        static bool logEnabled;
        static std::ofstream fout;
        static const char* FILE;
        static const std::ios::openmode MODE = std::ios::in | std::ios::out;
    };

}