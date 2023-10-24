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
    loadMDThread_ = std::make_unique<std::thread>([this] {Loading();});
    return 0;
}

void MDLoader::Run()
{
    keepRunning_.store(true);
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
            INFO("all MD loaded");
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
    INFO("MDLoader: start load date {}", currDate_);
    //TODO 
    std::string filename = "EXCHANGE_BINANCE.BTC-USDT.SECURITY_TYPE_PERP.CONTRACT_TYPE_LINEAR.USDT.UNSPECIFIED_bookSnapshot5_20230101.csv";
    csvLoader_->LoadFile(filePath + filename);
    while (LoadOneBatch())
    {
        std::size_t batchNum = mdCache_->BatchNumInCache();
        if (batchNum >= maxBatchInCache_)
        {
            std::this_thread::sleep_for
            (
                std::chrono::milliseconds(loadIntervalMs_)
            );
            continue;
        }
    }
}

bool MDLoader::LoadOneBatch()
{
    auto batch = std::make_shared<MDBatch>();
    for (uint32_t i = 0; i < oneBatchLines_; i++)
    {
        if (!csvLoader_->NextRow())
        {
            return false;
        }
        batch->emplace_back(csvLoader_->ToOrderbookSnapshort());
    }
    mdCache_->emplace_back(batch);
    
    return true;
}










};
};