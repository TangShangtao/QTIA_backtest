/**
 * 撮合订单, 产生成交事件, 触发回调
*/
#pragma once

#include "Protocol.h"
#include "BaseClass/Subscriber.h"
#include "OrderQueue.h"

#include <unordered_set>

namespace QB
{
namespace Matcher
{

class TradePublisher : MDSubscriber
{
protected:
    std::unordered_set<TradeSubscriberSPtr> subscribers_;
    std::shared_ptr<OrderQueue> orderQueue_ = std::make_shared<OrderQueue>(); 
protected:
    virtual void MatchOrder(OBSSPtr marketData) {};

public:
    virtual void OnBacktestInit() override {};
    virtual void OnBacktestStart() override {};
    virtual void OnBacktestEnd() override {};

    virtual void OnMDUpdate(OBSSPtr marketData) override;
    void Subscribe(TradeSubscriberSPtr subscriber);
protected:
    void RtnOrder(OrderSPtr order);
    void RtnTrade(TradeSPtr trade);
    void RspCancel(OrderSysID orderSysID, OrderRef orderRef);
public:
    void OrderInsert(OrderSPtr order);
    void OrderCancel(OrderSysID orderSysID, OrderRef orderRef);

};


};
};