#pragma once

#include <iostream>

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <yaml-cpp/yaml.h>

namespace QB
{
namespace ToolKit
{
int InitLogger(const YAML::Node& config);
int InitLogger(const std::string& configFilePath);
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

