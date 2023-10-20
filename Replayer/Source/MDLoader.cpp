#include "MDLoader.h"
#include "Logger.h"
#include "TimeUtils.h"
#include "Protocol.h"

#include <magic_enum.hpp>

namespace QB
{
using namespace ToolKit;

namespace Replayer
{

int MDLoader::Init(const YAML::Node& config)
{
    oneBatchSecs_ = config["oneBatchSecs"].as<DeltaSecs>(60);
    if (oneBatchSecs_ > MAX_ONE_BATCH_SECS)
    {
        ERROR("load a batch of MD failed, \
        reason: oneBatchSecs > max one batch secs({})", MAX_ONE_BATCH_SECS);
        return -1;
    }
    maxBatchInCache_ = config["maxBatchInCache"].as<DeltaSecs>(0);
    loadIntervalMs_ = config["loadIntervalMs"].as<DeltaMilliSecs>(0);
    if (maxBatchInCache_ == 0 || loadIntervalMs_ == 0)
    {
        ERROR("load a batch of MD failed, \
        reason: invaild maxBatchInCache({}) loadInterval({})", maxBatchInCache_, loadIntervalMs_);
    }
    startTs_ = TimeUtils::ISO2TS(config["start"].as<ISODatetime>());
    endTs_ = TimeUtils::ISO2TS(config["end"].as<ISODatetime>());
    if (startTs_ == 0 || endTs_ == 0)
    {
        ERROR("load backtest time range failed, \
        reason: invaild ISODatetime start({}), end({})", startTs_, endTs_);
        return -1;
    }
    const std::string mdTypeStr = config["MDType"].as<std::string>();
    mdType_ = magic_enum::enum_cast<MDType>(mdTypeStr).value();
    currBacthStartTs_ = startTs_;
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
        if (currBacthStartTs_ >= endTs_)
        {
            INFO("all MD loaded");
            keepRunning_.store(false);
            LoadOver.store(true);
            break;
        }
        std::size_t batchNum = mdCache_->BatchNumInCache();
        // 缓存已满
        if (batchNum >= maxBatchInCache_)
        {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(loadIntervalMs_)
            );
            continue;
        }
        // 缓存未满
        LoadOneBatch();
        // TODO
    }
}

void MDLoader::LoadOneBatch()
{
    TimeStamp currBatchEndTs = currBacthStartTs_ + oneBatchSecs_ * 1000;
    if (currBatchEndTs > endTs_)
    {
        currBacthStartTs_ = endTs_;
    }
    // TODO 从数据库读取一个Batch的数据
}










};
};