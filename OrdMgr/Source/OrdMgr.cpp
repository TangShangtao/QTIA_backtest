#include "OrdMgr.h"

namespace QB
{

OrderRef OrdMgr::NextOrderRef()
{
    return ++currOrderRef_;
}

OrderRef OrdMgr::OrderInsert(OrderSPtr order)
{
    order->orderRef = NextOrderRef();
    matcher_->OrderInsert(order);

    // LogOrder(order);        // TODO 补充OrdMgr功能
    
    return currOrderRef_;
}

void OrdMgr::OrderCancel(OrderSysID orderSysID, OrderRef orderRef)
{
    matcher_->OrderCancel(orderSysID, orderRef);
}

void OrdMgr::OnRtnOrder(OrderSPtr order)
{
    // LogOrder(order);        // TODO 补充OrdMgr功能

}

void OrdMgr::OnRtnTrade(TradeSPtr trade)
{
    // LogTrade(trade);        // TODO 补充OrdMgr功能

}
};