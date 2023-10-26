#pragma once 

#include "Constant/Enum.h"
#include "Constant/Using.h"
#include "Constant/Constexpr.h"

#include <string>
#include <memory>
#include <array>

namespace QB
{

class MDHeader
{
public:
    // ExchangeType exchange;
    // SymbolType   symbolType;
    std::string  symbol;

    TimeStamp    ts;
    // TimeStamp    localTs;
    
    // MDType       mdType;
    // std::string  toStr() const;
    // std::string  getTopicPrefix() const;
    // std::string  toJson() const;
};

class IncrementalOrderBookL2
{
public:
    // MDHeader mdHeader;
    // bool isSnapShot_;
    std::string  symbol;        // 合约名
    TimeStamp    ts;
    SideType side;
    double   price;
    double   volume;
};
using IOBSPtr = std::shared_ptr<IncrementalOrderBookL2>;
using IOBUPtr = std::unique_ptr<IncrementalOrderBookL2>;

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
    std::string  symbol;        // 合约名
    TimeStamp    ts;
    // Depth asks[MAX_DEPTH_LEVEL];
    // Depth bids[MAX_DEPTH_LEVEL];
    std::array<Depth, MAX_DEPTH_LEVEL> asks;
    std::array<Depth, MAX_DEPTH_LEVEL> bids;
};
using OBSSPtr = std::shared_ptr<OrderBookSnapShots>;
using OBSUPtr = std::unique_ptr<OrderBookSnapShots>;

};