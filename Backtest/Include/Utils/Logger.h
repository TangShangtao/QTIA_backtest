#pragma once

#include "Constant/Marco.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Logger
{
private:
    std::shared_ptr<spdlog::logger> logger_;
    bool is_init = false;
    // static spdlog::basic_logger_mt<spdlog::async_factory> async_logger_; 
public:
    static Logger& GetInstance()
    {
        static Logger instance;
        return instance;
    }
    void InfoLog(const std::string& msg)
    {
        init();
        logger_->info(msg);

    }
private:
    void init()
    {
        if (is_init == false)
        {
            spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
            logger_ = spdlog::stdout_color_mt("logger");
            is_init = true;
        }
    }
};

