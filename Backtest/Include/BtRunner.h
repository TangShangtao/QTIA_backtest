#pragma once
#include <string>
#include <iostream>
#include "Replayer/Include/Runner.h"
#include "Strategy/Include/StrategyBase.h"
#include "Matcher/Include/SimpleMatcher.h"
#include "Protocol.h"
#include "Logger.h"

namespace QB
{
class BtRunner
{
private:
    std::shared_ptr<Replayer::Runner> runner_;
    Matcher::TradePublisherSPtr matcher_;
    Strategy::StrategySPtr strategy_;
public:
    BtRunner(Strategy::StrategySPtr yourStrategy);
    void Init(const std::string& configPath);
    void Run()
    {
        runner_->Run();
    }
};
};