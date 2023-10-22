/**
 * 撮合订单, 产生成交事件, 触发回调
*/
#pragma once

#include "Protocol.h"
#include "BaseClass/Subscriber.h"

#include <map>
#include <deque>
#include <unordered_set>
namespace QB
{
namespace Matcher
{

class TradePublisher : MDSubscriber
{
protected:
    OrderRef currentID_ = 0;                                    // 生产OrderSysID;
    std::unordered_set<TradeSubscriberSPtr> subscribers_;

    std::map<double, std::deque<OrderSPtr>> price2OrderQueue_;  // 订单队列(TODO 解耦出去)
protected:
    virtual void MatchOrder(OBSSPtr marketData) {};

public:
    virtual void OnBacktestInit() override {};
    virtual void OnBacktestStart() override {};
    virtual void OnBacktestEnd() override {};

    virtual void OnMDUpdate(OBSSPtr marketData) override;
    void Subscribe(TradeSubscriberSPtr subscriber);
protected:
    const OrderSysID NextOrderSysID();
    void RtnOrder(OrderSPtr order, bool isSucc);
    void RtnTrade(TradeSPtr trade, bool isSucc);

public:
    void OrderInsert(OrderSPtr order);
    void OrderCancel(OrderSysID orderSysID, OrderRef orderRef);

};


};
};