/**
 * 历史数据加载器, 从哪里加载、如何加载历史数据--与数据库的对接
*/

#pragma once

#include "MDCache.h"
#include "Protocol.h"
#include "CsvLoader.h"

#include <atomic>
#include <thread>
#include <yaml-cpp/yaml.h>


namespace QB
{
namespace Replayer
{


class MDLoader
{
friend class MDPublisher;
private:
    std::atomic_bool keepRunning_ = false;
    std::unique_ptr<std::thread> loadMDThread_ = nullptr;
    std::shared_ptr<MDCache> mdCache_;
    std::shared_ptr<ToolKit::CsvLoader> csvLoader_ = std::make_shared<ToolKit::CsvLoader>();         // TODO

    uint32_t oneBatchLines_;
    uint32_t maxBatchInCache_;
    DeltaMilliSecs loadIntervalMs_;
    DateTime start_;
    DateTime end_;
    std::string path_;
    // MDType mdType_;

    DateTime currDate_;
    InstrumentName instrument_;  

public:
    std::atomic_bool LoadOver;

public:
    ~MDLoader();
public:
    int     Init(const YAML::Node& config, std::shared_ptr<MDCache> cache);
    void    Run();
    void    Stop();
private:
    void    Loading();
    void    LoadOneDay();
    bool    LoadOneBatch();


};





};
};