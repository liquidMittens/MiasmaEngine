#ifndef MIASMALOGGER_H_
#define MIASMALOGGER_H_

#include <format>

namespace utility
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error
    };

    class MiasmaLogger
    {
    public:
        template<typename... Args>
        static void Log(LogLevel level, std::format_string<Args...> fmt, Args&&... args)
        {
            std::string prefix;

            switch (level)
            {
            case LogLevel::Info:    prefix = "[INFO] "; break;
            case LogLevel::Warning: prefix = "[WARN] "; break;
            case LogLevel::Error:   prefix = "[ERROR] "; break;
            }

            std::cout
                << prefix
                << std::format(fmt, std::forward<Args>(args)...)
                << '\n';
        }
    };
}

#endif