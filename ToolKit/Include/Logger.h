#pragma once

#include <iostream>

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <yaml-cpp/yaml.h>

namespace QB{
namespace ToolKit{

int InitLogger(const YAML::Node& config)
{
    try
    {
        const auto loggerName = config["loggerName"].as<std::string>();
        const auto queueSize = config["queueSize"].as<std::uint32_t>();
        const auto backingThreadsCount = config["backingThreadsCount"].as<std::uint32_t>();
        spdlog::init_thread_pool(queueSize, backingThreadsCount);

        const auto outputDir      = config["outputDir"].as<std::string>();
        const auto outputFilename = config["outputFilename"].as<std::string>();
        const auto maxFiles       = config["maxFiles"].as<std::uint32_t>();
        const auto maxSize        = config["maxSize"].as<std::uint32_t>();
        const auto rotatingSinkPattern = config["rotatingSinkPattern"].as<std::string>();
        const auto stdoutSinkPattern   = config["stdoutSinkPattern"].as<std::string>();
        
        const auto logFileDebug = fmt::format("{}/{}.log.debug", outputDir, outputFilename);
        const auto logFileInfo  = fmt::format("{}/{}.log.info", outputDir, outputFilename);
        const auto logFileWarn  = fmt::format("{}/{}.log.debug", outputDir, outputFilename);
        const auto logFileError = fmt::format("{}/{}.log.debug", outputDir, outputFilename);
        
        const auto rotatingSinkDebug = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFileDebug, maxSize, maxFiles);
        const auto rotatingSinkInfo  = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFileInfo, maxSize, maxFiles);
        const auto rotatingSinkWarn  = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFileWarn, maxSize, maxFiles);
        const auto rotatingSinkError = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFileError, maxSize, maxFiles);
        rotatingSinkDebug->set_level(spdlog::level::debug);
        rotatingSinkInfo->set_level(spdlog::level::info);
        rotatingSinkWarn->set_level(spdlog::level::warn);
        rotatingSinkError->set_level(spdlog::level::err);
        rotatingSinkDebug->set_pattern(rotatingSinkPattern);
        rotatingSinkInfo->set_pattern(rotatingSinkPattern);
        rotatingSinkWarn->set_pattern(rotatingSinkPattern);
        rotatingSinkError->set_pattern(rotatingSinkPattern);

        const auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        stdoutSink->set_level(spdlog::level::info);
        stdoutSink->set_pattern(stdoutSinkPattern);

        std::vector<spdlog::sink_ptr> sinks{rotatingSinkDebug, rotatingSinkInfo, rotatingSinkWarn, rotatingSinkError};
        auto asyncLogger = std::make_shared<spdlog::async_logger>(loggerName, sinks.begin(), sinks.end(), spdlog::thread_pool(), \
        spdlog::async_overflow_policy::overrun_oldest);
        spdlog::register_logger(asyncLogger);
        spdlog::set_level(spdlog::level::trace);

        spdlog::set_default_logger(asyncLogger);
    }
    catch(const std::exception& e)
    {
        std::cerr << 
        fmt::format("Read logger config failed, error: {}", e.what()) 
                  << std::endl;
        return -1;
    }
    return 0;
    
}

int InitLogger(const std::string& configFilePath)
{
    YAML::Node config;
    try
    {
        config = YAML::LoadFile(configFilePath);
    }
    catch(const std::exception& e)
    {
        std::cerr << 
        fmt::format("Load logger config file failed, error: {}", e.what()) 
                  << std::endl;
        return -1;
    }
    return InitLogger(config);
}

};
};

#define DEBUG(...)                              \
{                                               \
    auto logger = spdlog::default_logger();     \
    SPDLOG_LOGGER_DEBUG(logger, __VA_ARGS__);   \
}
#define INFO(...)                               \
{                                               \
    auto logger = spdlog::default_logger();     \
    SPDLOG_LOGGER_INFO(logger, __VA_ARGS__);    \
}
#define WARN(...)                               \
{                                               \
    auto logger = spdlog::default_logger();     \
    SPDLOG_LOGGER_WARN(logger, __VA_ARGS__);    \
}
#define ERROR(...)                              \
{                                               \
    auto logger = spdlog::default_logger();     \
    SPDLOG_LOGGER_ERROR(logger, __VA_ARGS__);   \
}

