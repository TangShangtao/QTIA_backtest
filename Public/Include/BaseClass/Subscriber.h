/**
 * 行情数据回调基类, 观察者模式
*/
#pragma once

#include "Protocol.h"

#include <memory>

namespace QB
{

class Subscriber
{
public:
    virtual void OnBacktestInit() = 0;

    virtual void OnBacktestStart() = 0;
    virtual void OnBacktestEnd() = 0;
    
    virtual void OnMarketDataUpdate(IOBSPtr marketData) {};
    virtual void OnMarketDataUpdate(OBSSptr marketData) {};
};
using SubscriberSPtr = std::shared_ptr<Subscriber>;
using SubscriberUPtr = std::unique_ptr<Subscriber>;
};