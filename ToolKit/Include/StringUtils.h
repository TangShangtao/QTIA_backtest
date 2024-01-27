#pragma once

#include "Protocol.h"
#include "Logger.h"

#include <string>

namespace QB
{
namespace ToolKit
{

class StringUtils
{
public:
    // ISODatime转换为TimeStamp
    static double stod_s(const std::string& str)
    {
        try
        {
            if (str.size() == 0) return 0;
            return std::stod(str);
        }
        catch(const std::exception& e)
        {
            ERROR("stod_s: error convert stod from {}", str);
            std::cerr << e.what() << std::endl;
            return 0;
        }
    }
};

};
};