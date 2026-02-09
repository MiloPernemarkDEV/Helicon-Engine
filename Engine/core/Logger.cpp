#include "Logger.h"

#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>


namespace Helicon
{

    void Logger::Init() 
    {
        static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
        plog::init(plog::debug, &consoleAppender);
        HEL_DEBUG("Initialized logger.");
    }

        void Logger::HLog(LogLevel level, const char* message) {
    // ANSI Escape Codes
    const char* colorReset = "\x1B[0m";
    const char* colorRed   = "\x1B[31m";
    const char* colorGreen = "\x1B[32m";
    const char* colorYellow= "\x1B[33m";
    const char* colorCyan  = "\x1B[36m";

    switch (level) {
        case LogLevel::Debug:   
            PLOGD << colorCyan << message << colorReset; 
            break;
        case LogLevel::Info:    
            PLOGI << colorGreen << message << colorReset; 
            break;
        case LogLevel::Warning: 
            PLOGW << colorYellow << message << colorReset; 
            break;
        case LogLevel::Error:   
            PLOGE << colorRed << message << colorReset; 
            break;
    }
}
}