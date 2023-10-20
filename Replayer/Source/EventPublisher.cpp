#include "MDPublisher.h"
#include "Logger.h"

namespace QB
{
using namespace ToolKit;

namespace Replayer
{

void MDPublisher::Register(MDSubscriberSPtr MDSubscriber)
{
    MDSubscribers_.emplace(MDSubscriber);
}

int MDPublisher::Init(std::shared_ptr<MDLoader> loader)
{
    loader_ = loader;
    consumeMDThread_ = std::make_unique<std::thread>([this] {Publishing();});
    for (auto it : MDSubscribers_)
    {
        it->OnBacktestInit();
    }
    return 0; 
}

void MDPublisher::Run()
{
    keepRunning_.store(true);
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
    for (auto it : MDSubscribers_)
    {
        it->OnBacktestStart();
    }
    while (keepRunning_.load())
    {
        std::size_t batchNum = mdCache_->BatchNumInCache();
        if (batchNum == 0 && loader_->LoadOver.load() == true)
        {
            INFO("all event published");
            keepRunning_.store(false);
            break;
        }
        // 缓存已空
        if (batchNum == 0)
        {
                std::this_thread::sleep_for(
                std::chrono::milliseconds(loader_->loadIntervalMs_)
            );
        }
        // 缓存未空
        PublishOneBatch();
    }
    for (auto it : MDSubscribers_)
    {
        it->OnBacktestEnd();
    }

}

void MDPublisher::PublishOneBatch()
{

}

};
};