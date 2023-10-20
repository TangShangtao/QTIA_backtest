/**
 * 策略基类
*/
#pragma once
#include "Protocol.h"

#include "BaseClass/Subscriber.h"

namespace QB
{

class Strategy : MDSubscriber, TradeSubscriber
{
public:
    virtual void OnBacktestInit() override {};

    virtual void OnBacktestStart() override {};
    virtual void OnBacktestEnd() override {};
    
    virtual void OnMDUpdate(IOBSPtr marketData) override {};
    virtual void OnMDUpdate(OBSSptr marketData) override {};

public:

    virtual void OnRtnOrder(Order order) override {};
    virtual void OnRtnTrade(Trade trade) override {};

};

class StrategyApi
{
public:
    static StrategyApi* CreateApi();
    virtual bool SubscribeMD(const std::string symbol);
    virtual OrderRef OrderInsert(Order order);
    virtual bool OrderCancel(OrderSysID orderSysID, OrderRef orderRef);

};
using QBApi = std::shared_ptr<StrategyApi>;

};

