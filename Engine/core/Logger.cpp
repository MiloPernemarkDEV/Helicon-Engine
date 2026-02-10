#include "Logger.h"

#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Formatters/MessageOnlyFormatter.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <filesystem>

namespace Helicon
{   
    void Logger::Init() 
    {        
        const std::string logDirectory = "Logs";
        if (!std::filesystem::exists(logDirectory))
        {
            std::filesystem::create_directory(logDirectory);
        }

        static plog::ConsoleAppender<plog::MessageOnlyFormatter> consoleAppender;

        static plog::RollingFileAppender<plog::TxtFormatter> fileAppender("Logs/Helicon.log", 1000000, 2);

        plog::init(plog::debug, &consoleAppender);

        plog::get()->addAppender(&fileAppender);

        HEL_DEBUG("Logger Init called");
    }

    void Logger::HLog(LogLevel level, const char* message, const char* file, int line) 
    {

        const char* colorReset = "\x1B[0m";
        const char* colorRed   = "\x1B[31m";
        const char* colorGreen = "\x1B[32m";
        const char* colorYellow= "\x1B[33m";
        const char* colorCyan  = "\x1B[36m";

        switch (level) 
        {
            case LogLevel::Debug:   
                PLOGD << file << ":" << " " << colorCyan << line << "." << " " << message << colorReset;
                break;
            case LogLevel::Info:    
                PLOGI << file << ":" << " " << colorGreen << line << "." << " " << message << colorReset;
                break;
            case LogLevel::Warning: 
                PLOGW << file << ":" << " " << colorYellow << line << "." << " " << message << colorReset;
                break;
            case LogLevel::Error:   
                PLOGE << file << ":" << " " << colorRed << line << "." << " " << message << colorReset;
                break;
        }
    }
}