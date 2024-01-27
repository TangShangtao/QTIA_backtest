#pragma once
#include <map>
#include <deque>
#include <mutex>

#include "Protocol.h"

namespace QB
{
namespace Matcher
{

// 注意线程安全
class OrderQueue
{
using Queue = std::map<double, std::deque<OrderSPtr>>;
public:
    Queue buyQue;
    std::mutex buyQueMutex;
    Queue sellQue;
    std::mutex sellQueMutex;
    OrderRef currentID = 0;                                    // 生产OrderSysID;

public:
    OrderSPtr OrderInsert(OrderSPtr order);
    OrderSPtr OrderCancel(OrderSysID orderSysID, OrderRef orderRef);

private:
    const OrderSysID NextOrderSysID();
    void  InsertToQueue(const OrderSPtr order, bool isBuy, double price);
};



};
};
