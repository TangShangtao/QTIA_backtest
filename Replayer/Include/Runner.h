#pragma once

#include "EventPublisher.h"
// #include "MDCache.h"
#include "MDLoader.h"

#include <memory>

namespace QB
{
namespace Replayer
{

class Runner
{
private:
    std::shared_ptr<EventPublisher> publisher_;
    std::shared_ptr<MDCache> mdCache_;
    std::shared_ptr<MDLoader> loader_;

public:
    int Init(const YAML::Node& config)
    {
        loader_->Init(config);
        publisher_->Init(loader_);
    }
    void Register(SubscriberSPtr Subscriber)
    {
        publisher_->Register(Subscriber);
    }
    void Run()
    {
        loader_->Run();
        publisher_->Run();
    }
    void Stop()
    {
        loader_->Stop();
        publisher_->Stop();
    }


};


};
};