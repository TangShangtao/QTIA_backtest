#pragma once

#include "Constant/Enum.h"
#include "Constant/Using.h"

#include <string>
#include <memory>

namespace QB
{

class Order
{
public:
    OrderRef     orderref_;         // 内部订单ID
    OrderSysID   orderSysID_;       // 模拟交易所订单ID

    ExchangeType exchange_;         // 交易所
    std::string  symbol_;           // 合约名
    SymbolType   symbolType_;       // 合约类型

    SideType     side_;             // 买卖方向
    OffsetType   offset_;           // 开平方向
    double       orderPrice_;       // 下单价
    double       orderVolume_;      // 下单量
    PriceType    priceType_;        // 订单类型

    TimeStamp    insertTime_;       // 下单时间
    double       fee_;              // 手续费
    CurrencyType feeCurr_;          // 手续费币种

    double       unfilledVolume_;   // 未成交数量
    OrderStatus  status_;           // 订单状态


};
using OrderSPtr = std::shared_ptr<Order>;
using OrderUPtr = std::unique_ptr<Order>;


};
