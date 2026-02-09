#pragma once
#include "dllDefines.h" 

// Needs to be updated to tell where the log is called from

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

        // Variadic template or simple string for loggings
        static void HLog(LogLevel level, const char* message);
    };
}

// Shortcut macros for easier use throughout the engine
#define HEL_INFO(msg)  ::Helicon::Logger::HLog(::Helicon::LogLevel::Info, msg)
#define HEL_WARN(msg)  ::Helicon::Logger::HLog(::Helicon::LogLevel::Warning, msg)
#define HEL_ERROR(msg) ::Helicon::Logger::HLog(::Helicon::LogLevel::Error, msg)
#define HEL_DEBUG(msg) ::Helicon::Logger::HLog(::Helicon::LogLevel::Debug, msg)