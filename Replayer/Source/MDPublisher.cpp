#include "MDPublisher.h"
#include "Logger.h"

namespace QB
{
using namespace ToolKit;

namespace Replayer
{
MDPublisher::~MDPublisher()
{
    if (consumeMDThread_->joinable())
    {
        consumeMDThread_->join();
    }
}
void MDPublisher::Register(MDSubscriberSPtr MDSubscriber)
{
    MDSubscribers_.emplace(MDSubscriber);
}

int MDPublisher::Init(std::shared_ptr<MDLoader> loader, std::shared_ptr<MDCache> cache)
{
    loader_ = loader;
    mdCache_ = cache;
    for (auto subscriber : MDSubscribers_)
    {
        subscriber->OnBacktestInit();
    }
    return 0; 
}

void MDPublisher::Run()
{
    keepRunning_.store(true);
    consumeMDThread_ = std::make_unique<std::thread>([this] {Publishing();});
}

void MDPublisher::Stop()
{
    keepRunning_.store(false);
    if (consumeMDThread_->joinable())
    {
        consumeMDThread_->join();
    }
}

void MDPublisher::Publishing()
{
    for (auto subscriber : MDSubscribers_)
    {
        subscriber->OnBacktestStart();
    }
    while (keepRunning_.load())
    {
        // INFO("MDPublisher: mdCache num {}", mdCache_->BatchNumInCache());
        if (mdCache_->BatchNumInCache() == 0 && (loader_->LoadOver.load() == true))
        {
            INFO("all event published");
            keepRunning_.store(false);
            for (auto subscriber : MDSubscribers_)
            {
                subscriber->OnBacktestEnd();
            }
            return;
        }
        // 缓存已空
        while (mdCache_->BatchNumInCache() == 0 && (loader_->LoadOver.load() == false))
        {
            DEBUG("MDPublisher: 缓存已空");
            std::this_thread::sleep_for
            (
                std::chrono::milliseconds(loader_->loadIntervalMs_)
            );
        }
        // 缓存未空
        PublishOneBatch();
    }
    for (auto subscriber : MDSubscribers_)
    {
        subscriber->OnBacktestEnd();
    }
}

void MDPublisher::PublishOneBatch()
{
    DEBUG("MDPublisher: mdCache num {}, Cache ref {}", mdCache_->BatchNumInCache(), mdCache_.use_count());
    auto batch = mdCache_->front();
    for (const auto data : batch)              // TODO 空指针
    {
        for (auto subscriber : MDSubscribers_)
        {
            subscriber->OnMDUpdate(data);
        }        
    }
    mdCache_->pop();
}

};
};