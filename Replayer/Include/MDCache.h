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
#include <vector>
namespace QB
{
namespace Replayer
{

// template<typename T>
// class MDBatch
// {
// public:
//     OBSSPtr batch_[T];
// };
using MDBatch = std::vector<OBSSPtr>;

class MDCache
{
public:
    std::deque<MDBatch> cache_;
    std::mutex cacheMutex_;

public:
    void pop();
    MDBatch front();
    void emplace_back(const MDBatch& batch);
    std::size_t BatchNumInCache();

};
};



};

