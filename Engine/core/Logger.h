  ////////////// 
  // Logger.h //
  //////////////

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