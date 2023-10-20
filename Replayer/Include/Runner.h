#pragma once

#include "MDPublisher.h"
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
    std::shared_ptr<MDPublisher> publisher_;
    std::shared_ptr<MDCache> mdCache_;
    std::shared_ptr<MDLoader> loader_;

public:
    int Init(const YAML::Node& config)
    {
        loader_->Init(config);
        publisher_->Init(loader_);
    }
    void Register(MDSubscriberSPtr MDSubscriber)
    {
        publisher_->Register(MDSubscriber);
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