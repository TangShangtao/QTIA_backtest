#include "MDCache.h"
#include "Logger.h"
namespace QB
{
namespace Replayer
{

void MDCache::pop()
{
    std::lock_guard<std::mutex> lock(cacheMutex_);
    cache_.pop_front();
}
std::shared_ptr<MDBatch> MDCache::front()
{
    std::lock_guard<std::mutex> lock(cacheMutex_);
    std::shared_ptr<MDBatch> batch = cache_.front();
    return batch;
}


void MDCache::emplace_back(const std::shared_ptr<MDBatch> batch)
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