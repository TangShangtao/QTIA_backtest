#pragma once

#include <cinttypes>
#include <string>

namespace QB
{
// enum
enum class ExchangeType : std::uint16_t
{
  Okex,
  Binance,
  Coinbase,
  Kraken,

  QBExchange,
  Others = UINT16_MAX - 1
};

enum class SymbolType : std::uint8_t
{
  Spot,
  Futures,
  CFutures,
  Perp,
  CPerp,
  Option,
  index,

  Others = UINT8_MAX - 1
};

enum class CurrencyType : std::uint8_t
{
    USD,
    USDT,
    BTC

};

enum class SideType : std::uint8_t
{
    Bid,
    Ask,

    Others = UINT8_MAX - 1
};

enum class OffsetType : std::uint8_t
{
    Open,
    Close,

    Others = UINT8_MAX - 1
};

enum class PosDirectionType : std::uint8_t
{
    Long,
    Short,
    Both,
    Others = UINT8_MAX - 1
};

// 只考虑限价单
enum class PriceType : std::uint8_t 
{ 
    Limit, 
    Others = UINT8_MAX - 1 
};

// 基于tardis提供的行情数据
enum class MDType : std::uint8_t
{
    IncrementalOrderBookL2,
    OrderBookSnapShots,
    // Trades,

    Others = UINT8_MAX - 1
};

enum class OrderStatus : std::uint8_t
{
    Created,
    // ConfirmedInLocal = 3,
    // Pending = 5,
    // ConfirmedByExch = 10,
    Queuening,
    PartialFilled,
    AllFilled,
    Canceled,
    PartialFilledCanceled,

};

enum class CloseType
{
    AllowClsTD,
    AllowClsYD,

    Others = UINT8_MAX - 1
};

};