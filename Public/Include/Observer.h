// created by tangshangtao 0916
// learn to use observer pattern
#pragma once

#include "Constant/Enum.h"
#include "Constant/Marco.h"
#include "Data/Orderbook.h"
#include "Data/IncrementalOrderbook.h"

#include <unordered_set>
NAMESPACE_BEGIN

// observe orderbook data
class OrderbookObserver
{
    virtual void OnDepthLevl1(DepthLvl1* data) {};
    virtual void OnDepthLevl5(DepthLvl5* data) {};
    virtual void OnDepthLevl10(DepthLvl10* data) {};
    virtual void OnDepthLevl25(DepthLvl25* data) {};

    virtual void OnInit() = 0;
    virtual void OnReplayBegin() = 0;
    virtual void OnReplayDone() = 0;
};

// process raw data from exchange
class ExchangeObserver
{
protected:
    std::unordered_set<OrderbookObserver*> orderbook_observers_;
public:
    virtual void OnIncrementalOrderbook(IncrementalOrderbook rawData) = 0;
    
    virtual void OnInit() = 0;
    virtual void OnReplayBegin() = 0;
    virtual void OnReplayDone() = 0;

    void RegisterObserver(OrderbookObserver* observer)
    {
        orderbook_observers_.insert(observer);
    }
};


NAMESPACE_END;