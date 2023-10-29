#include <iostream>
#include "Replayer/Include/Runner.h"
#include "Strategy/Include/StrategyBase.h"
#include "Protocol.h"
#include "Logger.h"

using namespace QB::Replayer;
using namespace QB;
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

class TestStra : public QB::Strategy::StrategyBase
{
public:
    // 1739837
    virtual void OnBacktestInit() override {INFO("OnBacktestStart: Init");}

    virtual void OnBacktestStart() override {INFO("OnBacktestStart: Start");}
    virtual void OnBacktestEnd() override {INFO("OnBacktestStart: End");}
    
    // virtual void OnMDUpdate(IOBSPtr marketData) override {};
    // virtual void OnMDUpdate(OBSSPtr marketData) override {};
    // virtual void OnMDUpdate(OBSSPtr marketData) override {std::cout << marketData->ts << std::endl;}
    virtual void OnMDUpdate(OBSSPtr marketData) override {}

public:

    virtual void OnRtnOrder(OrderSPtr order) override {};
    virtual void OnRtnTrade(TradeSPtr trade) override {};
};

int main()
{
    // ToolKit::Logger::Init("./config/logger.yaml");
    auto runner = Runner();
    auto config = Load("./config/backtestconfig.yaml");
    auto stra = std::make_shared<TestStra>();

    runner.Register(stra);

    runner.Init(config["replayer"]);
    runner.Run();
}