#pragma once

#include <cinttypes>
#include <string>

namespace QB
{
// UNIX时间戳(毫秒)
using TimeStamp = std::uint64_t;
// 时间间隔(毫秒秒, 正)
using DeltaMilliSecs = std::uint64_t;
using DeltaSecs = std::uint32_t;
using ISODatetime = std::string;
using OrderRef = std::uint64_t;
using OrderSysID = std::string;

};