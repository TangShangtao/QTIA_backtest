#include <iostream>
#include "Replayer/Include/Runner.h"
#include "Strategy/Include/StrategyBase.h"
#include "Matcher/Include/SimpleMatcher.h"
#include "Protocol.h"
#include "Logger.h"

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

class TestStra : public Strategy::StrategyBase
{
private:
    int i_ = 0;
public:
    // 1739837
    virtual void OnBacktestInit() override {INFO("OnBacktestStart: Init");}

    virtual void OnBacktestStart() override {INFO("OnBacktestStart: Start");}
    virtual void OnBacktestEnd() override {INFO("OnBacktestStart: End");}
    
    virtual void OnMDUpdate(OBSSPtr marketData) override 
    {
        INFO("OnMDUpdate: {}", marketData->asks[0].Price);
        if (i_ < 1)
        {
            auto order = std::make_shared<Order>();
            order->direction = DirectionType::Buy;
            order->orderPrice = 35;
            order->orderVolume = 100;
            order->offset = OffsetType::Open;
            api_->OrderInsert(order);
            i_++;
        }


    }
    virtual void OnRtnOrder(OrderSPtr order) override
    {
        INFO("RtnOrder: order status {}", (uint32_t)order->status);
    }
    virtual void OnRtnTrade(TradeSPtr trade) override
    {
        INFO("RtnTrade: trade amount {}", trade->tradeVolume);
    }
    TestStra(Matcher::TradePublisherSPtr matcher) : Strategy::StrategyBase(matcher)
    {}
};

int main()
{
    // ToolKit::Logger::Init("./config/logger.yaml");
    auto runner = std::make_shared<Replayer::Runner>();
    auto matcher = std::make_shared<Matcher::SimpleMatcher>();
    auto config = Load("./config/backtestconfig.yaml");
    auto stra = std::make_shared<TestStra>(matcher);

    runner->Register(stra);
    runner->Register(matcher);
    matcher->Register(stra);

    runner->Init(config["replayer"]);
    matcher->Init(5);
    runner->Run();
}