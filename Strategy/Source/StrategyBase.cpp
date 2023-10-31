#include "StrategyBase.h"

namespace QB
{

namespace Strategy
{

OrderRef StrategyApi::OrderInsert(OrderSPtr order)
{
    return ordMgr_->OrderInsert(order);
}

void StrategyApi::OrderCancel(OrderSysID orderSysID, OrderRef orderRef)
{
    ordMgr_->OrderCancel(orderSysID, orderRef);
}

void StrategyApi::AddMatcher(Matcher::TradePublisherSPtr matcher)
{
    ordMgr_ = std::make_shared<OrdMgr>(matcher);
}

void StrategyBase::AddMatcher(Matcher::TradePublisherSPtr matcher)
{
    api_ = std::make_shared<StrategyApi>();
    api_->AddMatcher(matcher);
}

};
};