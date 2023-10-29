#include "OrderQueue.h"

#include <thread>
#include <future>

namespace QB
{
namespace Matcher
{

void OrderQueue::InsertToQueue(const OrderSPtr order, bool isBuy, double price)
{
    if (isBuy)
    {
        std::lock_guard<std::mutex> lock(buyQueMutex);
        auto it = buyQue.find(price);
        if (it == buyQue.end())
        {
            buyQue[price] = std::deque<OrderSPtr>{order};
        }
        else
        {
            auto& que = it->second;
            que.emplace_back(order);
        }
    }
    else
    {
        std::lock_guard<std::mutex> lock(sellQueMutex);
        auto it = sellQue.find(price);
        if (it == sellQue.end())
        {
            sellQue[price] = std::deque<OrderSPtr>{order};
        }
        else
        {
            auto& que = it->second;
            que.emplace_back(order);
        }
    }
}

OrderSPtr OrderQueue::OrderInsert(OrderSPtr order)
{
    order->status = OrderStatus::Queuening;
    order->orderSysID = NextOrderSysID();
    double price = order->orderPrice;
    DirectionType direction = order->direction;
    switch (direction)
    {
    case DirectionType::Buy:
        InsertToQueue(order, true, price);
        break;
    case DirectionType::Sell:
        InsertToQueue(order, false, price);
        break;
    default:
        break;
    }
    return order;
}

OrderSPtr OrderQueue::OrderCancel(OrderSysID orderSysID, OrderRef orderRef)
{
    auto checkBuyQue = [this, orderSysID, orderRef]() -> OrderSPtr
    {
        std::lock_guard<std::mutex> lock(buyQueMutex);
        for (auto& pair : buyQue)
        {
            auto& orderQueue = pair.second;
            for (auto it = orderQueue.begin(); it != orderQueue.end(); ++it)
            {
                if (it->get()->orderSysID == orderSysID && it->get()->orderRef == orderRef)
                {
                    it->get()->status = OrderStatus::Canceled;
                    orderQueue.erase(it);
                    return *it;
                }
            }
        }
        return nullptr;
    };
    auto checkSellQue = [this, orderSysID, orderRef]() -> OrderSPtr
    {
        for (auto& pair : sellQue)
        {
            std::lock_guard<std::mutex> lock(sellQueMutex);
            auto& orderQueue = pair.second;
            for (auto it = orderQueue.begin(); it != orderQueue.end(); ++it)
            {
                if (it->get()->orderSysID == orderSysID && it->get()->orderRef == orderRef)
                {
                    it->get()->status = OrderStatus::Canceled;
                    orderQueue.erase(it);
                    return *it;
                }
            }
        }
        return nullptr;
    };
    auto resultBuyQue = std::async(std::launch::async, checkBuyQue);
    auto resultSellQue = std::async(std::launch::async, checkSellQue);
    if (resultBuyQue.get() != nullptr)
    {
        return resultBuyQue.get();
    }
    else if (resultSellQue.get() != nullptr)
    {
        return resultBuyQue.get();
    }
    else
    {
        return nullptr;
    }
}

const OrderSysID OrderQueue::NextOrderSysID()
{
    ++currentID;
    // const OrderSysID orderSysID = "QB" + std::to_string(currentID);
    return std::string("QB") + std::to_string(currentID);
}

};
};





