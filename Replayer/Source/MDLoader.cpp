#include "MDLoader.h"
#include "Logger.h"
#include "Protocol.h"

namespace QB
{
namespace Replayer
{

int MDLoader::Init(const YAML::Node& config)
{
    oneBatchSecs_ = config["oneBatchSecs"].as<DeltaSecs>(60);
    if (oneBatchSecs_ > MAX_ONE_BATCH_SECS)
    {
        WARN("load a batch of MD failed, \
        reason: oneBatchSecs > max one batch secs({})", MAX_ONE_BATCH_SECS);
        return -1;
    }


}










};
};