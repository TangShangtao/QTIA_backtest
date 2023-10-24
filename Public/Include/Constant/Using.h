#pragma once

#include <cinttypes>
#include <string>

namespace QB
{

using TimeStamp = std::uint64_t;            // UNIX时间戳(毫秒)
using DeltaMilliSecs = std::uint64_t;       // 时间间隔(毫秒秒, 正)
using DeltaSecs = std::uint32_t;            
using DateTime = std::uint32_t;             // 日期(20230101) 
using OrderRef = std::uint64_t;
using OrderSysID = std::string;
using TradeID = std::string;
};