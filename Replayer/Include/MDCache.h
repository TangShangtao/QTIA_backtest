/**
 * 历史数据缓存, 如何高效的将历史数据存放在内存中--数据结构相关优化
*/
#pragma once

#include "Protocol.h"

#include <string>
#include <memory>
#include <map>
#include <deque>
#include <mutex>
namespace QB
{
namespace Replayer
{
class MDBatch
{
public:
    MDType      mdType_;
    TimeStamp   localTs_;
    DeltaMilliSecs   interval_;
    std::string data_;
};
using MDBatchSPtr = std::shared_ptr<MDBatch>;
using TsMDBatchSPtrMap = std::map<TimeStamp, MDBatchSPtr>;

class MDCache
{
public:
    std::deque<std::shared_ptr<TsMDBatchSPtrMap>> cache_;
    std::mutex cacheMutex_;

public:
    std::shared_ptr<TsMDBatchSPtrMap> pop();


};
};



};

