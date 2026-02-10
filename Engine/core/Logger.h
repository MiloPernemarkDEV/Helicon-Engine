  ////////////// 
  // Logger.h //
  //////////////

/*
  The logger Logs to a log file and to the console.
  Each log file has a max size in bytes if it is reached the file gets renamed and a new log file is made
  There is a limit to how many files can be created when it is reached the oldest log file is deleted
*/ 

// Todo, add functionality to clear the log files, not important rightnow

#pragma once
#include "dllDefines.h" 

namespace Helicon
{
    enum class LogLevel 
    {
        Debug,
        Info,
        Warning,
        Error
    };

    class ENGINE_API Logger 
    {
        public:
            static void Init();

            static void HLog(LogLevel level, const char* message, const char* file, int line);
        };
    }

#define HEL_INFO(msg)  ::Helicon::Logger::HLog(::Helicon::LogLevel::Info, msg, __FILE__, __LINE__)
#define HEL_WARN(msg)  ::Helicon::Logger::HLog(::Helicon::LogLevel::Warning, msg, __FILE__, __LINE__)
#define HEL_ERROR(msg) ::Helicon::Logger::HLog(::Helicon::LogLevel::Error, msg, __FILE__, __LINE__)
#define HEL_DEBUG(msg) ::Helicon::Logger::HLog(::Helicon::LogLevel::Debug, msg, __FILE__, __LINE__)