/**
 * 事件生成器, 大循环遍历数据, 产生事件并触发回调--与其他部分对接 
*/
#pragma once
#include "MDCache.h"
#include "MDLoader.h"
#include "BaseClass/Subscriber.h"

#include <atomic>
#include <thread>
#include <yaml-cpp/yaml.h>
#include <unordered_set>
namespace QB
{
namespace Replayer
{

class EventPublisher
{
private:
    std::atomic_bool keepRunning_{false};
    std::unique_ptr<std::thread> consumeMDThread_{nullptr};
    std::shared_ptr<MDCache> mdCache_;
    std::shared_ptr<MDLoader> loader_;
    std::unordered_set<SubscriberSPtr> subscribers_;

public:
    void    Register(SubscriberSPtr Subscriber);   // Register在Init前被调用

    int     Init(std::shared_ptr<MDLoader> loader);

    void    Run();
    void    Stop();
private:
    void    Publishing();
    void    PublishOneBatch();
public:
    EventPublisher(const EventPublisher&) = delete;
    EventPublisher& operator=(const EventPublisher&) = delete;
    EventPublisher(const EventPublisher&&) = delete;
    EventPublisher& operator=(const EventPublisher&&) = delete;

    explicit EventPublisher() {}

};

};

};