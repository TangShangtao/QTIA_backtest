#pragma once

#include "Protocol.h"

#include <yaml-cpp/yaml.h>
#include <tuple>

namespace QB
{
namespace Database
{
    
class DBClient
{
public:
    virtual int Init(const YAML::Node& config);

    virtual std::tuple<int, std::string, int, std::string> Query(const std::string& sql, TimeStamp start, TimeStamp end);

};

};


};