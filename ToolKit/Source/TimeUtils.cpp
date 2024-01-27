#include "TimeUtils.h"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
namespace QB
{
namespace ToolKit
{

// TimeStamp TimeUtils::ISO2TS(const ISODatetime& iso)
// {
//     return 1;
// }
TimeStamp TimeUtils::GetTimeStampNow()
{
    std::time_t now = std::time(nullptr);
    std::tm* current_time = std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(current_time, "%y:%m:%d:%H:%M:%S");
    std::string time_str = oss.str();

    return time_str;
}

};
};