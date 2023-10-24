#include "MDCache.h"

namespace QB
{
namespace Replayer
{

std::shared_ptr<MDBatch> MDCache::pop()
{
    std::lock_guard<std::mutex> lock(cacheMutex_);
    auto batch = cache_.front();
    cache_.pop_front();
    return batch;
}

void MDCache::emplace_back(std::shared_ptr<MDBatch> batch)
{
    std::lock_guard<std::mutex> lock(cacheMutex_);
    cache_.emplace_back(batch);    
}

std::size_t MDCache::BatchNumInCache()
{
    std::lock_guard<std::mutex> lock(cacheMutex_);
    return cache_.size();
}

};
};