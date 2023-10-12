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
private:
    std::atomic_bool keepRunning{false};
    std::unique_ptr<std::thread> loadMDThread{nullptr};
    std::unique_ptr<MDCache> mdCache_;
    DeltaSecs oneBatchSecs_;
    TimeStamp exchTsStart_;
    TimeStamp exchTsEnd_;
    TimeStamp localTsStart_;
    TimeStamp localTsEnd_;
    TimeStamp currBacthStartTs_;
public:
    int     Init(const YAML::Node& config);
    void    Run();
    void    Stop();


public:
    MDLoader(const MDLoader&) = delete;
    MDLoader& operator=(const MDLoader&) = delete;
    MDLoader(const MDLoader&&) = delete;
    MDLoader& operator=(const MDLoader&&) = delete;

    explicit MDLoader() {}


};





};
};