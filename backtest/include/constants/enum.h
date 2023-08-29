//
// Created by TangShangtao on 2023/8/28.
// Enum declaration
//

#pragma once

enum InstrumentType
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
enum InstrumentTypeClass
{
    Spot,
    ForwardFuture,
    ReverseFuture,
    Quanto,
    CFD
};
// TODO 
enum CurrencyType
{
    USD,
    USDT,
    BTC
};
// TODO
enum ExchangeType
{
    HuobiPerpUSDT,
    HuobiPerpUSDTCross,
    Bitasset,
    BinanceUsdMargin,
    NewOkcoinUSDT,
    Ftx,
    BitMEX,
    Ig,
    Yahoo

};