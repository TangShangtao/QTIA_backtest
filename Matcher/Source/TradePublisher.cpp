#include "TradePublisher.h"
#include "Logger.h"
namespace QB
{
namespace Matcher
{
const OrderSysID TradePublisher::NextOrderSysID()
{
    ++currentID_;
    // const OrderSysID orderSysID = "QB" + std::to_string(currentID_);
    return std::string("QB") + std::to_string(currentID_);
}

void TradePublisher::OnMDUpdate(OBSSPtr marketData)
{
    MatchOrder(marketData);
}

void TradePublisher::Subscribe(TradeSubscriberSPtr subscriber)
{
    subscribers_.emplace(subscriber);
}

void TradePublisher::RtnOrder(OrderSPtr order, bool isSucc)
{
    for (const auto& subscriber : subscribers_)
    {
        subscriber->OnRtnOrder(order, isSucc);
    }
}

void TradePublisher::RtnTrade(TradeSPtr trade, bool isSucc)
{
    for (const auto& subscriber : subscribers_)
    {
        subscriber->OnRtnTrade(trade, isSucc);
    }
}

void TradePublisher::OrderInsert(OrderSPtr order)
{
    order->status = OrderStatus::Queuening;
    order->orderSysID = NextOrderSysID();
    RtnOrder(order, true);
    INFO("Matcher: order received, orderSysId {}, OrderRef {}", order->orderSysID, order->orderRef);

    double price = order->orderPrice;
    auto& orderQueue = price2OrderQueue_[price];
    orderQueue.emplace_back(order);
}
void TradePublisher::OrderCancel(OrderSysID orderSysID, OrderRef orderRef)
{
    for (auto& pair : price2OrderQueue_)
    {
        auto& OrderQueue = pair.second;
        for (auto it = OrderQueue.begin(); it != OrderQueue.end(); ++it)
        {
            if (it->get()->orderSysID == orderSysID && it->get()->orderRef == orderRef)
            {
                INFO("Matcher: order cancelled, orderSysId {}, orderRef {}", orderSysID, orderRef);
                it->get()->status = OrderStatus::Canceled;
                RtnOrder(*it, true);
                OrderQueue.erase(it);
                return;
            }
        }
    }
    INFO("Matcher: order cancel failed, orderSysId {}, orderRef {}", orderSysID, orderRef)
    OrderSPtr order = std::make_shared<Order>();
    RtnOrder(order, false);
}



};
};