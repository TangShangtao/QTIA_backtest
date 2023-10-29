#include "SimpleMatcher.h"

namespace QB
{
namespace Matcher
{
// 注意OrderQueue的线程安全
void SimpleMatcher::MatchOrder(OBSSPtr marketData)
{
    // TODO 线程池, 每次行情来，创建两个线程去撮合买队列和卖队列

}

void SimpleMatcher::MatchLogic(OBSSPtr marketData)
{
    std::lock_guard<std::mutex> lock(orderQueue_->buyQueMutex);
    auto it = orderQueue_->buyQue.begin();
    for (; it != orderQueue_->buyQue.end(); it++)
    {
        auto& deque = it->second;
    }
}


};
};