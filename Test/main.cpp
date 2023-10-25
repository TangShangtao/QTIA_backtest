#include <iostream>
#include "Replayer/Include/Runner.h"
#include "Strategy/Include/StrategyBase.h"
#include "Protocol.h"

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
    virtual void OnBacktestInit() override {std::cout << "OnBacktestStart: Init" << std::endl;};

    virtual void OnBacktestStart() override {std::cout << "OnBacktestStart: Start" << std::endl;};
    virtual void OnBacktestEnd() override {std::cout << "OnBacktestStart: End" << std::endl;};
    
    // virtual void OnMDUpdate(IOBSPtr marketData) override {};
    virtual void OnMDUpdate(OBSSPtr marketData) override {};
    // virtual void OnMDUpdate(OBSSPtr marketData) override {std::cout << marketData->ts << std::endl;}

public:

    virtual void OnRtnOrder(OrderSPtr order, bool isSucc) override {};
    virtual void OnRtnTrade(TradeSPtr trade, bool isSucc) override {};
};

int main()
{
    auto runner = Runner();
    auto config = Load("./config/backtestconfig.yaml");
    auto stra = std::make_shared<TestStra>();

    runner.Register(stra);

    runner.Init(config["replayer"]);
    runner.Run();
}