#include "Logger.h"

#include <filesystem>

#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Formatters/MessageOnlyFormatter.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>


namespace Helicon
{   
    bool Logger::hcInitializeEngineLogger() 
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

       
        HLog(LogLevel::Debug, "Logger Init.", __FILE__, __LINE__);
        return HC_SUCCESS;
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
            case LogLevel::Error:   
                PLOGE << file << ":" << " " << colorRed << line << "." << " " << message << colorReset;
                break;
        }
    }

    void Logger::hcShutdownLogger()
    {
        Z_LOG("Logger shutdown.");
        // Todo 
    }
}