/**
 * 策略基类
*/
#pragma once
#include "Protocol.h"

#include "BaseClass/Subscriber.h"
#include "OrdMgr/Include/OrdMgr.h"

namespace QB
{
namespace Strategy
{

class StrategyBase : MDSubscriber, TradeSubscriber
{
public:
    virtual void OnBacktestInit() override {};

    virtual void OnBacktestStart() override {};
    virtual void OnBacktestEnd() override {};
    
    // virtual void OnMDUpdate(IOBSPtr marketData) override {};
    virtual void OnMDUpdate(OBSSPtr marketData) override {};

public:

    virtual void OnRtnOrder(OrderSPtr order, bool isSucc) override {};
    virtual void OnRtnTrade(TradeSPtr trade, bool isSucc) override {};
protected:
    QBApi api_;
};

class StrategyApi
{
public:
    bool SubscribeMD(const std::string symbol);
    OrderRef OrderInsert(OrderSPtr order);
    void OrderCancel(OrderSysID orderSysID, OrderRef orderRef);
private:
    std::shared_ptr<OrdMgr> ordMgr_;
};
using QBApi = std::shared_ptr<StrategyApi>;


};



};

