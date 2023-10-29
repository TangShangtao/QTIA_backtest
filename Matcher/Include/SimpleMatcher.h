#include "TradePublisher.h"

namespace QB
{
namespace Matcher
{

class SimpleMatcher : TradePublisher
{
private:
    
private:
    virtual void MatchOrder(OBSSPtr marketData) override;
    void MatchBuyQue(OBSSPtr marketData);
    void MatchSellQue(OBSSPtr marketData);
    void MatchOneBuyDeque(std::deque<OrderSPtr>& deque, const std::array<Depth, MAX_DEPTH_LEVEL>& asks);
    void MatchOneSellDeque(std::deque<OrderSPtr>& deque, const std::array<Depth, MAX_DEPTH_LEVEL>& bids);
    TradeSPtr BuildTradeFromOrder(const OrderSPtr order);
};

};
};