//
// Created by TangShangtao on 2023/8/28.
// Enum declaration
//

#pragma once

enum class InstrumentType
{
    Spot,
    FutureThisWeek,
    FutureNextWeek,
    FutureThisQuarter,
    FutureNextQuarter,
    FuturePerp,
    FutureLTFX,
    FutureIndex,
    Option, 
    Forex   
};
enum class InstrumentTypeClass
{
    Spot,
    ForwardFuture,
    ReverseFuture,
    Quanto,
    CFD
};
// TODO 
enum class CurrencyType
{
    USD,
    USDT,
    BTC
};
// TODO
enum class ExchangeType
{
    HuobiPerpUSDT,
    HuobiPerpUSDTCross,
    Bitasset,
    BinanceUsdMargin,
    BinanceCoinMargin,
    NewOkcoinUSDT,
    Ftx,
    BitMEX,
    Ig,
    Yahoo

};

enum class SideType
{
    Bid,
    ask
};