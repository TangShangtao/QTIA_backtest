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
    ExchangeType exchange_;
    SymbolType   symbolType_;
    std::string  symbol_;

    TimeStamp    ts_;
    TimeStamp    localTs_;
    
    MDType       mdType_;
    // std::string  toStr() const;
    // std::string  getTopicPrefix() const;
    // std::string  toJson() const;
};

class IncrementalOrderBookL2
{
public:
    MDHeader mdHeader_;
    // bool isSnapShot_;
    SideType side_;
    double   price_;
    double   volume_;
};
using IOBSptr = std::shared_ptr<IncrementalOrderBookL2>;
using IOBUPtr = std::unique_ptr<IncrementalOrderBookL2>;

struct Depth
{
    double price_;
    double volume_;
    std::uint32_t level_;
};

class OrderBookSnapShots
{
public:
    MDHeader                           mdHeader_;
    std::array<Depth, MAX_DEPTH_LEVEL> asks_;
    std::array<Depth, MAX_DEPTH_LEVEL> bids_;

};
using OBSSptr = std::shared_ptr<OrderBookSnapShots>;
using OBSUPtr = std::unique_ptr<OrderBookSnapShots>;

};