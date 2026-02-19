  ////////////// 
  // Logger.h //
  //////////////

/*
  The logger Logs to a log file and to the console.
  Each log file has a max size in bytes if it is reached the file gets renamed and a new log file is made
  There is a limit to how many files can be created when it is reached the oldest log file is deleted
*/ 

// Todo, add functionality to clear the log files, not important right now
// Consider adding init/shutdown log macros for each system to be able to adjust them from here instead of every file 

#pragma once
#include "Defines.h" 


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
            static bool hcInitializeEngineLogger();

            static void HLog(LogLevel level, const char* message, const char* file, int line);

            // Not doing anything yet 
            static void hcShutdownLogger();
        };
}

#ifdef _DEBUG
  #define HE_LOG(message) ::Helicon::Logger::HLog(::Helicon::LogLevel::Debug, message, __FILE__, __LINE__)
  #define HE_LOG_INFO(message)  ::Helicon::Logger::HLog(::Helicon::LogLevel::Info, message, __FILE__, __LINE__)
  #define HE_LOG_WARNING(message)  ::Helicon::Logger::HLog(::Helicon::LogLevel::Warning, message, __FILE__, __LINE__)
  #define HE_LOG_ERROR(message) ::Helicon::Logger::HLog(::Helicon::LogLevel::Error, message, __FILE__, __LINE__)
  #define HE_LOG_DEBUG(message) ::Helicon::Logger::HLog(::Helicon::LogLevel::Debug, message, __FILE__, __LINE__)
#else
  #define HE_LOG(...)
  #define HE_LOG_INFO(...)
  #define HE_LOG_WARNING(...)
  #define HE_LOG_ERROR(...)
  #define HE_LOG_DEBUG(...) 
#endif