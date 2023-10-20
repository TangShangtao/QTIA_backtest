#pragma once

#include "Protocol.h"

namespace QB
{
namespace ToolKit
{

class TimeUtils
{
public:
    // ISODatime转换为TimeStamp
    static TimeStamp ISO2TS(const ISODatetime& iso);
    
};

};
};