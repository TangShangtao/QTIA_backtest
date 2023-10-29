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


};
};