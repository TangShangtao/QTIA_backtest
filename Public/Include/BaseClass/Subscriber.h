/**
 * 行情数据回调基类, 观察者模式
*/
#pragma once

#include "Protocol.h"

#include <memory>

namespace QB
{

class MDSubscriber
{
public:
    virtual void OnBacktestInit() = 0;

    virtual void OnBacktestStart() = 0;
    virtual void OnBacktestEnd() = 0;
    
    // virtual void OnMDUpdate(IOBSPtr marketData) {};
    virtual void OnMDUpdate(OBSSPtr marketData) = 0;
    virtual ~MDSubscriber() {}
};
using MDSubscriberSPtr = std::shared_ptr<MDSubscriber>;
using MDSubscriberUPtr = std::unique_ptr<MDSubscriber>;


class TradeSubscriber
{
public:
    // TODO 改为异步
    virtual void OnRtnOrder(OrderSPtr order) = 0;
    virtual void OnRtnTrade(TradeSPtr trade) = 0;
    virtual void OnRspCancel(OrderSysID orderSysID, OrderRef orderRef) {}   // 撤单失败回调
    virtual ~TradeSubscriber() {};
};
using TradeSubscriberSPtr = std::shared_ptr<TradeSubscriber>;
using TradeSubscriberUPtr = std::unique_ptr<TradeSubscriber>;
};