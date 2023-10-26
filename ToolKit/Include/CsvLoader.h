#pragma once
// TODO 迁移到Replayer中
#include "Protocol.h"

#include <fstream>
#include <cstdint>
#include <vector>
#include <unordered_map>

namespace QB
{
namespace ToolKit
{
class CsvLoader
{
private:
    MDType mdType_ = MDType::OrderBookSnapShots;
    std::ifstream ifs_;
public:
    std::string Column = "";
    std::string CurrentRow = "";
public:

    bool    LoadFile(const std::string& Path);
    bool    NextRow();
    OBSSPtr ToOrderbookSnapshort();
private:
    std::vector<std::string> split(const std::string& data);

};


};
};