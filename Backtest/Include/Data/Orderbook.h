//
// Created by Lingxiao XU on 2023/8/27.
// Modified by TangShangtao on 2023/09/04
//

#pragma once

#include "Constants/Marco.h"

#include <cinttypes>
#include <cstring>
#include <ostream>
#include <array>

NAMESPACE_BEGIN

struct OrderBookLevel 
{
    double price{};
    std::int64_t volume{};
};

inline std::ostream& operator << (std::ostream& os, const OrderBookLevel md) 
{
    return os << "price=" << md.price << "volume=" << md.volume;
}

template <std::int8_t N>
class DepthImpl 
{
    static constexpr  std::int8_t klevel{N};
//        Instrument instrument {};
    std::int64_t timestamp{};
    std::array<OrderBookLevel, N> bid_level{};
    std::array<OrderBookLevel, N> ask_level{};

    [[nodiscard]] const DepthImpl<N>& GetDepthState() const {return *this;}

//        [[nodiscard]] const Instrument& GetInstrument() const {return instrument;}

    template<std::int8_t M>
    DepthImpl<M> Truncate() const 
    {
        DepthImpl<M> rst{};
//            rst.instrument = instrument;
        rst.timestamp = timestamp;
        constexpr auto L = std::min(M, N);
        std::memcpy(rst.bid_level.data(), bid_level.data(), sizeof(OrderBookLevel) * L);
        std::memcpy(rst.ask_level.data(), ask_level.data(), sizeof(OrderBookLevel) * L);
        return rst;
    }
};

using DepthLvl1 = DepthImpl<1>;
using DepthLvl5 = DepthImpl<5>;
using DepthLvl10 = DepthImpl<10>;
using DepthLvl25 = DepthImpl<25>;

template <size_t N>
inline std::ostream& operator<<(std::ostream& os, const DepthImpl<N>& md) 
{
    os << "instrument: " << md.instrument << '\n'
        << "timestamp: " << md.timestamp << '\n'
        << "ask_price: [ ";
    for (const auto &e : md.ask_level) 
    {
        os << e.price << ' ';
    }
    os << "]\n" << "bid_price: [";
    for (const auto &e : md.bid_level) 
    {
        os << e.price << ' ';
    }
    os << "]\n" << "ask_volume: [";
    for (const auto &e : md.ask_level) 
    {
        os << e.volume << ' ';
    }
    for (const auto &e : md.bid_level) 
    {
        os << e.volume << ' ';
    }
}
NAMESPACE_END;

