#include "BtRunner.h"

YAML::Node Load(const std::string& configFilePath)
{
    try
    {
        return YAML::LoadFile(configFilePath);
    }
    catch(const std::exception& e)
    {
        std::cerr << 
        fmt::format("Load logger config file failed, error: {}", e.what()) 
                << std::endl;
        YAML::Node config;
        return config;
    }
}

namespace QB
{

BtRunner::BtRunner(Strategy::StrategySPtr yourStrategy)
{
    runner_ = std::make_shared<Replayer::Runner>();
    matcher_ = std::make_shared<Matcher::SimpleMatcher>();
    strategy_ = yourStrategy;
    strategy_->AddMatcher(matcher_);
    runner_->Register(strategy_);
    runner_->Register(matcher_);
    matcher_->Register(strategy_);
}
void BtRunner::Init(const std::string& configPath)
{
    auto config = Load(configPath);
    runner_->Init(config["replayer"]);
    matcher_->Init(5);
}
};