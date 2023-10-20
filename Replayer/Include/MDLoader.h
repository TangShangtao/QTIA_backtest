/**
 * 历史数据加载器, 从哪里加载、如何加载历史数据--与数据库的对接
*/

#pragma once

#include "MDCache.h"

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
    std::atomic_bool keepRunning_{false};
    std::unique_ptr<std::thread> loadMDThread_{nullptr};
    std::shared_ptr<MDCache> mdCache_;

    DeltaSecs oneBatchSecs_;
    std::size_t maxBatchInCache_;
    DeltaMilliSecs loadIntervalMs_;
    TimeStamp startTs_;
    TimeStamp endTs_;
    TimeStamp currBacthStartTs_;
    
    MDType mdType_;
public:
    std::atomic_bool LoadOver;
    
public:
    int     Init(const YAML::Node& config);
    void    Run();
    void    Stop();
private:
    void    Loading();
    void    LoadOneBatch();

public:
    MDLoader(const MDLoader&) = delete;
    MDLoader& operator=(const MDLoader&) = delete;
    MDLoader(const MDLoader&&) = delete;
    MDLoader& operator=(const MDLoader&&) = delete;

    explicit MDLoader() {}


};





};
};