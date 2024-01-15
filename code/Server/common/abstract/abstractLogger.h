#ifndef ABSTRACT_LOGGER_H
#define ABSTRACT_LOGGER_H

#include <iostream> 
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class AbstractLogger {
public:
    AbstractLogger(const std::string& loggerName) {
        // Create a logger with a console sink
        logger = std::make_shared<spdlog::logger>(loggerName, std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        
        // Set the log pattern (customize as needed)
        logger->set_pattern("[%Y-%m-%d %H:%M:%S:%e] [%^%l%$] [%n] [%t] %v");
    }

    virtual ~AbstractLogger() = default;

    std::shared_ptr<spdlog::logger> logger;
};

#endif