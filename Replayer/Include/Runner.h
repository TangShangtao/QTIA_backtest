#pragma once

#include "MDPublisher.h"
// #include "MDCache.h"
#include "MDLoader.h"
#include <fmt/format.h>
#include <memory>

namespace QB
{
namespace Replayer
{

class Runner
{
private:
    std::shared_ptr<MDPublisher> publisher_ = std::make_shared<MDPublisher>();
    std::shared_ptr<MDCache> mdCache_ = std::make_shared<MDCache>();
    std::shared_ptr<MDLoader> loader_ = std::make_shared<MDLoader>();

public:

    int Init(const YAML::Node& config)
    {
        loader_->Init(config, mdCache_);
        publisher_->Init(loader_, mdCache_);
        return 0;
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