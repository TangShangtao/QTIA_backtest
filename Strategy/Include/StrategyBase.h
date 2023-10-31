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

class StrategyApi
{
public:
    OrderRef OrderInsert(OrderSPtr order);
    void OrderCancel(OrderSysID orderSysID, OrderRef orderRef);
public:
    explicit StrategyApi(Matcher::TradePublisherSPtr matcher)
    {
        ordMgr_ = std::make_shared<OrdMgr>(matcher);
    }
private:
    std::shared_ptr<OrdMgr> ordMgr_;
};
using QBApi = std::shared_ptr<StrategyApi>;

class StrategyBase : public MDSubscriber, public TradeSubscriber
{
public:
    virtual void OnBacktestInit() = 0;

    virtual void OnBacktestStart() = 0;
    virtual void OnBacktestEnd() = 0;
    
    // virtual void OnMDUpdate(IOBSPtr marketData) override {};
    virtual void OnMDUpdate(OBSSPtr marketData) = 0;

public:

    virtual void OnRtnOrder(OrderSPtr order) = 0;
    virtual void OnRtnTrade(TradeSPtr trade) = 0;
    virtual ~StrategyBase() {}
public:
    StrategyBase(Matcher::TradePublisherSPtr matcher)
    {
        api_ = std::make_shared<StrategyApi>(matcher);
    }
protected:
    QBApi api_;
};

};
};





