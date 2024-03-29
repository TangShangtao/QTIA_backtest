#include "MDLoader.h"
#include "Logger.h"
// #include "TimeUtils.h"
#include "Protocol.h"

#include <magic_enum.hpp>

namespace QB
{
using namespace ToolKit;

namespace Replayer
{

MDLoader::~MDLoader()
{
    if (loadMDThread_ != nullptr && loadMDThread_->joinable())
    {
        loadMDThread_->join();
    }
}
int MDLoader::Init(const YAML::Node& config, std::shared_ptr<MDCache> cache)
{
    mdCache_ = cache;
    oneBatchLines_ = config["oneBatchLines"].as<uint32_t>(60);
    maxBatchInCache_ = config["maxBatchInCache"].as<uint32_t>(0);
    loadIntervalMs_ = config["loadIntervalMs"].as<DeltaMilliSecs>(0);
    start_ = config["start"].as<DateTime>(0);
    end_ = config["end"].as<DateTime>(0);
    path_ = config["path"].as<std::string>();
    currDate_ = start_;
    instrument_ = config["instrument"].as<std::string>();
    return 0;
}

void MDLoader::Run()
{
    keepRunning_.store(true);
    loadMDThread_ = std::make_unique<std::thread>([this] {Loading();});

}

void MDLoader::Stop()
{
    keepRunning_.store(false);
    if (loadMDThread_->joinable())
    {
        loadMDThread_->join();
    }
}

void MDLoader::Loading()
{
    while (keepRunning_.load())
    {
        // 缓存完毕
        if (currDate_ > end_)
        {
            DEBUG("all MD loaded");
            keepRunning_.store(false);
            LoadOver.store(true);       // 信号量通知
            return;
        }
        // 缓存未满


        LoadOneDay();
        currDate_++;
    }
}

void MDLoader::LoadOneDay()
{
    std::string filePath = path_ + "/" + std::to_string(currDate_) + "/";
    DEBUG("MDLoader: start load date {}", currDate_);
    //TODO 
    bool isLoaded = csvLoader_->LoadFile(filePath + instrument_);

    if (!isLoaded)
    {
        keepRunning_.store(false);
        LoadOver.store(true);
        return;
    }
    while (LoadOneBatch())
    {
        while (mdCache_->BatchNumInCache() >= maxBatchInCache_)
        {
            DEBUG("MDLoader: batch num in cache > max batch in cache");
            std::this_thread::sleep_for
            (
                std::chrono::milliseconds(loadIntervalMs_)
            );
        }
    }
}

bool MDLoader::LoadOneBatch()
{
    auto batch = MDBatch();
    for (uint32_t i = 0; i < oneBatchLines_; i++)
    {
        if (!csvLoader_->NextRow())
        {
            DEBUG("meet eof");
            mdCache_->emplace_back(batch);
            return false;
        }
        batch.emplace_back(csvLoader_->ToOrderbookSnapshort());
    }

    mdCache_->emplace_back(batch);
    DEBUG("MDLoader: mdCache num {}, Cache ref {}", mdCache_->BatchNumInCache(), mdCache_.use_count());
    return true;
}










};
};