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
    virtual void OnMDUpdate(OBSSPtr marketData) {};
};
using MDSubscriberSPtr = std::shared_ptr<MDSubscriber>;
using MDSubscriberUPtr = std::unique_ptr<MDSubscriber>;


class TradeSubscriber
{
public:
    // TODO 改为异步
    virtual void OnRtnOrder(OrderSPtr order, bool isSucc) {};
    virtual void OnRtnTrade(TradeSPtr trade, bool isSucc) {};
};
using TradeSubscriberSPtr = std::shared_ptr<TradeSubscriber>;
using TradeSubscriberUPtr = std::unique_ptr<TradeSubscriber>;
};