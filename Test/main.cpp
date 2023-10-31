#include <iostream>
#include "Replayer/Include/Runner.h"
#include "Strategy/Include/StrategyBase.h"
#include "Matcher/Include/SimpleMatcher.h"
#include "Protocol.h"
#include "Logger.h"
#include "Backtest/Include/BtRunner.h"

using namespace QB;

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
};

int main()
{
    // ToolKit::Logger::Init("./config/logger.yaml");
    auto yourStrategy = std::make_shared<TestStra>();
    BtRunner runner = BtRunner(yourStrategy);
    runner.Init("./config/backtestconfig.yaml");
    runner.Run();
}