#include "Constant/Enum.h"
#include "Constant/Using.h"

#include <string>
#include <memory>


namespace QB
{

class Trade
{
public:
    OrderRef     orderRef;         // 内部订单ID
    OrderSysID   orderSysID;       // 模拟交易所订单ID
    TradeID      tradeID;

    ExchangeType exchange;         // 交易所
    std::string  symbol;           // 合约名
    SymbolType   symbolType;       // 合约类型

    SideType     side;             // 买卖方向
    OffsetType   offset;           // 开平方向
    double       orderPrice;       // 下单价
    double       orderVolume;      // 下单量
    PriceType    priceType;        // 订单类型

    TimeStamp    insertTime;       // 下单时间
    double       fee;              // 手续费
    CurrencyType feeCurr;          // 手续费币种

    double       unfilledVolume;   // 未成交数量
    OrderStatus  status;           // 订单状态
};
using TradeSPtr = std::shared_ptr<Trade>;
using TradeUPtr = std::unique_ptr<Trade>;

};