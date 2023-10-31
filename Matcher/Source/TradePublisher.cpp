#include "TradePublisher.h"
#include "Logger.h"
namespace QB
{
namespace Matcher
{
void TradePublisher::Init(uint8_t OrderbookLevel)
{
    orderbookLevel_ = OrderbookLevel;
}

void TradePublisher::OnMDUpdate(OBSSPtr marketData)
{
    MatchOrder(marketData);
}

void TradePublisher::Register(TradeSubscriberSPtr subscriber)
{
    subscribers_.emplace(subscriber);
}

void TradePublisher::RtnOrder(OrderSPtr order)
{
    for (const auto& subscriber : subscribers_)
    {
        subscriber->OnRtnOrder(order);
    }
}

void TradePublisher::RtnTrade(TradeSPtr trade)
{
    for (const auto& subscriber : subscribers_)
    {
        subscriber->OnRtnTrade(trade);
    }
}

void TradePublisher::RspCancel(OrderSysID orderSysID, OrderRef orderRef)
{
    for (const auto& subscriber : subscribers_)
    {
        subscriber->OnRspCancel(orderSysID, orderRef);
    }
}


void TradePublisher::OrderInsert(OrderSPtr order)
{
    order = orderQueue_->OrderInsert(order);
    RtnOrder(order);
    INFO("Matcher: order received, orderSysId {}, OrderRef {}", order->orderSysID, order->orderRef);
    return;

}
void TradePublisher::OrderCancel(OrderSysID orderSysID, OrderRef orderRef)
{
    OrderSPtr order = orderQueue_->OrderCancel(orderSysID, orderRef);
    if (order == nullptr)
    {
        RspCancel(orderSysID, orderRef);
        INFO("Matcher: order cancel failed, orderSysId {}, orderRef {}", orderSysID, orderRef)
        return;
    }
    RtnOrder(order);
    INFO("Matcher: order cancelled, orderSysId {}, orderRef {}", orderSysID, orderRef);    
    return;

}

const TradeID TradePublisher::NextTradeID()
{
    ++currentTradeID;
    // const OrderSysID orderSysID = "QB" + std::to_string(currentID);
    return std::string("QBTrade") + std::to_string(currentTradeID);
}

};
};