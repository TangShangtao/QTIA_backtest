#pragma once

#include "Protocol.h"
#include "BaseClass/Subscriber.h"
#include "Matcher/Include/TradePublisher.h"

namespace QB
{

// TODO 记录订单信息的具体逻辑
class OrdMgr : TradeSubscriber
{
private:
    OrderRef currOrderRef_ = 0;
    Matcher::TradePublisherSPtr matcher_;       // TODO 使用动态加载
public:
    explicit OrdMgr(Matcher::TradePublisherSPtr matcher)
    {
        matcher_ = matcher;
    }
public:
    virtual void OnRtnOrder(OrderSPtr order) override;
    virtual void OnRtnTrade(TradeSPtr trade) override;
public:
    OrderRef OrderInsert(OrderSPtr order);
    void OrderCancel(OrderSysID orderSysID, OrderRef orderRef);

private:
    OrderRef NextOrderRef();
    void LogOrder(OrderSPtr order);
};


};
