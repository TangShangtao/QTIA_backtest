#pragma once

#include "Protocol.h"
#include "BaseClass/Subscriber.h"

namespace QB
{
class PosMgr : MDSubscriber, TradeSubscriber
{
public:
    virtual void OnBacktestInit() override;
    virtual void OnBacktestStart() override;
    virtual void OnBacktestEnd() override;
    
    virtual void OnMDUpdate(OBSSPtr marketData) override;
    
    virtual void OnRtnOrder(OrderSPtr order, bool isSucc) override;
    virtual void OnRtnTrade(TradeSPtr trade, bool isSucc) override;
    
};
};