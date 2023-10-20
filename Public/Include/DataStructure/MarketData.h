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
    ExchangeType exchange;
    SymbolType   symbolType;
    std::string  symbol;

    TimeStamp    ts;
    TimeStamp    localTs;
    
    MDType       mdType;
    // std::string  toStr() const;
    // std::string  getTopicPrefix() const;
    // std::string  toJson() const;
};

class IncrementalOrderBookL2
{
public:
    MDHeader mdHeader;
    // bool isSnapShot_;
    SideType side;
    double   price;
    double   volume;
};
using IOBSPtr = std::shared_ptr<IncrementalOrderBookL2>;
using IOBUPtr = std::unique_ptr<IncrementalOrderBookL2>;

struct Depth
{
    double price;
    double volume;
    std::uint32_t level;
};

class OrderBookSnapShots
{
public:
    MDHeader mdHeader_;
    std::array<Depth, MAX_DEPTH_LEVEL> asks;
    std::array<Depth, MAX_DEPTH_LEVEL> bids;

};
using OBSSptr = std::shared_ptr<OrderBookSnapShots>;
using OBSUPtr = std::unique_ptr<OrderBookSnapShots>;

};