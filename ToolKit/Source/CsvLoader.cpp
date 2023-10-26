#include "CsvLoader.h"
#include "Logger.h"
#include "StringUtils.h"
static int i = 0;
namespace QB
{
namespace ToolKit
{
bool CsvLoader::LoadFile(const std::string& Path)
{
    ifs_ = std::ifstream(Path);
    if (!ifs_.is_open())
    {
        ERROR("CsvLoader: open file {} failed", Path);
        return false;
    }
    std::getline(ifs_, Column);
    return true;
}
// 到eof返回false, 否则返回true
bool CsvLoader::NextRow()
{
    if (ifs_.eof()) return false;
    std::getline(ifs_, CurrentRow);
    return true;
}

OBSSPtr CsvLoader::ToOrderbookSnapshort()      
{
    auto data = std::make_shared<OrderBookSnapShots>();
    if (CurrentRow.length() == 0)
    {
        return data;
    }
    // 1672617599976000
    const auto fieldVec = split(CurrentRow);
    data->symbol = fieldVec[2];               // TODO 
    data->ts = fieldVec[3];
    for (int i = 5, j = 0; i <= 21; j++)    
    {
        data->asks[j] = Depth
        (
            std::stod(fieldVec[i++]),
            std::stod(fieldVec[i++])
        );
        data->bids[j] = Depth
        (
            std::stod(fieldVec[i++]),
            std::stod(fieldVec[i++])
        );
    }
    return data;
}


std::vector<std::string> CsvLoader::split(const std::string& str)
{
    std::vector<std::string> ret;
    size_t start, pos;
    start = 0;
    do
    {
        pos = str.find_first_of(",", start);
        if (pos == start)
        {
            ret.emplace_back("");
            start = pos + 1;
        }
        else if (pos == std::string::npos)
        {
            ret.emplace_back( str.substr(start) );
            break;
        }
        else
        {
            ret.emplace_back( str.substr(start, pos - start) );
            start = pos + 1;
        }

    } while (pos != std::string::npos);
    return ret;    
}


};
};
