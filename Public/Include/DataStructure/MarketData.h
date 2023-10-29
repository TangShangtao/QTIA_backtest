#pragma once 

#include "Constant/Enum.h"
#include "Constant/Using.h"
#include "Constant/Constexpr.h"

#include <string>
#include <memory>
#include <array>

namespace QB
{
class Depth
{
public:
    double Price = 0;
    double Volume = 0;
    Depth(double price, double volume)
    {
        Price = price;
        Volume = volume;
    }
    Depth() {}
};

class OrderBookSnapShots
{
public:
    // MDHeader mdHeader_;
    InstrumentName  instrument;                 // 合约名
    TimeStamp       ts;
    // Depth asks[MAX_DEPTH_LEVEL];
    // Depth bids[MAX_DEPTH_LEVEL];
    std::array<Depth, MAX_DEPTH_LEVEL> asks;    // 由低到高(0 - 卖1, 1 - 卖2) 
    std::array<Depth, MAX_DEPTH_LEVEL> bids;    // 由低到高(0 - 买1, 1 - 买2) 
};
using OBSSPtr = std::shared_ptr<OrderBookSnapShots>;
using OBSUPtr = std::unique_ptr<OrderBookSnapShots>;




};