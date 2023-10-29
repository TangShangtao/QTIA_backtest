#include "SimpleMatcher.h"

namespace QB
{
namespace Matcher
{
// 注意OrderQueue的线程安全
void SimpleMatcher::MatchOrder(OBSSPtr marketData)
{
    // TODO 线程池, 每次行情来，创建两个线程去撮合买队列和卖队列

}

void SimpleMatcher::MatchBuyQue(OBSSPtr marketData)
{
    std::lock_guard<std::mutex> lock(orderQueue_->buyQueMutex);
    auto it = orderQueue_->buyQue.begin();
    for (; it != orderQueue_->buyQue.end(); it++)
    {
        auto& deque = it->second;
        MatchOneBuyDeque(deque, marketData->asks);
    }
}

void SimpleMatcher::MatchSellQue(OBSSPtr marketData)
{
    std::lock_guard<std::mutex> lock(orderQueue_->sellQueMutex);
    auto it = orderQueue_->sellQue.rbegin();
    for (; it != orderQueue_->sellQue.rend(); it++)
    {
        auto& deque = it->second;
        MatchOneSellDeque(deque, marketData->bids);
    }
}

void SimpleMatcher::MatchOneBuyDeque(std::deque<OrderSPtr>& deque, std::array<Depth, MAX_DEPTH_LEVEL> asks)
{
    for (auto it = deque.begin(); it != deque.end(); it++)
    {
        auto order = *it;
        double orderPrice = order->orderPrice;
        double unfilledVolume = order->unfilledVolume;
        for (uint8_t i = 0; i < orderbookLevel_; i++)
        {
            Depth& depth = asks[i];
            double MDSellPrice = depth.Price;
            double MDSellVolume = depth.Volume;
            if (MDSellVolume == 0) {continue;}         // 若行情Orderbook当前level已消耗完, 用剩余行情继续撮合这个订单 
            if (MDSellPrice > orderPrice) {break;}     // 行情卖价 > 订单买价, 无法成交, 撮合下个订单
            if (unfilledVolume <= MDSellVolume)        // 可以成交, 可以全成
            {
                order->unfilledVolume = 0;
                order->status = OrderStatus::AllTraded;
                RtnOrder(order);
                auto trade = BuildTradeFromOrder(order);
                trade->tradePrice = (MDSellPrice + orderPrice) / 2;  // TODO 成交价计算逻辑
                trade->tradeVolume = unfilledVolume;
                RtnTrade(trade);
                deque.erase(it);
                depth.Volume -= trade->tradeVolume;     // 消耗行情Orderbook当前level
                break;                                  // 回报, 撮合下一个订单
            }
            order->unfilledVolume -= MDSellVolume;      // 可以成交, 可以部成
            order->status = OrderStatus::PartialTraded;
            RtnOrder(order);
            auto trade = BuildTradeFromOrder(order);
            trade->tradePrice = (MDSellPrice + orderPrice) / 2;  // TODO 成交价计算逻辑
            trade->tradeVolume = MDSellVolume;
            RtnTrade(trade);
            depth.Volume -= trade->tradeVolume;          // 消耗行情Orderbook当前level, 此处为0
            continue;                                    // 回报, 用剩余行情继续撮合这个订单
        }
    }
}

void SimpleMatcher::MatchOneSellDeque(std::deque<OrderSPtr>& deque, std::array<Depth, MAX_DEPTH_LEVEL> bids)
{

}

TradeSPtr SimpleMatcher::BuildTradeFromOrder(const OrderSPtr order)
{
    TradeSPtr trade;
    // trade->exchange
    // trade->fee
    // trade->feeCurr
    trade->insertTime = order->insertTime;
    trade->offset = order->offset;
    trade->orderPrice = order->orderPrice;
    trade->orderRef = order->orderRef;
    trade->orderSysID = order->orderSysID;
    trade->orderVolume = order->orderVolume;
    trade->priceType = order->priceType;
    trade->direction = order->direction;
    trade->symbol = order->symbol;
    trade->symbolType = order->symbolType;
    trade->tradeID = NextTradeID();
}


};
};