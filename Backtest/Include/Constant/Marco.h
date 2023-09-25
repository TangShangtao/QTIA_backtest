#pragma once

#include <cinttypes>

#include "Utils/Logger.h"

#define NAMESPACE_BEGIN namespace backtest {
#define NAMESPACE_END }
#define USING_NS using namespace backtest

#define INFO(msg) Logger::GetInstance().InfoLog(msg)

// TODO datastructure for timestamp and time duration
typedef std::uint64_t DateType;
typedef std::uint64_t TimeType;
typedef std::uint64_t DurationType;