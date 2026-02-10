#include "Logger.h"

#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Formatters/MessageOnlyFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>

namespace Helicon
{

    void Logger::Init() 
    {
        static plog::ConsoleAppender<plog::MessageOnlyFormatter> consoleAppender;
        plog::init(plog::debug, &consoleAppender);

        HEL_DEBUG("Logger Init called");
    }

        void Logger::HLog(LogLevel level, const char* message, const char* file, int line) {
    const char* colorReset = "\x1B[0m";
    const char* colorRed   = "\x1B[31m";
    const char* colorGreen = "\x1B[32m";
    const char* colorYellow= "\x1B[33m";
    const char* colorCyan  = "\x1B[36m";

    switch (level) {
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