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
    virtual void OnBacktestInit() override {std::cout << "Init" << std::endl;};

    virtual void OnBacktestStart() override {std::cout << "Start" << std::endl;};
    virtual void OnBacktestEnd() override {std::cout << "End" << std::endl;};
    
    // virtual void OnMDUpdate(IOBSPtr marketData) override {};
    virtual void OnMDUpdate(OBSSPtr marketData) override {std::cout << "Update" << std::endl;};

public:

    virtual void OnRtnOrder(OrderSPtr order, bool isSucc) override {};
    virtual void OnRtnTrade(TradeSPtr trade, bool isSucc) override {};
};

int main()
{
    auto runner = Runner();
    auto config = Load("./config/backtestconfig.yaml");

    runner.Init(config["replayer"]);
    auto stra = std::make_shared<TestStra>();
    runner.Register(stra);
}