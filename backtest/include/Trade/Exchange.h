//
// Created by TangShangtao on 2023/9/6.
//

#pragma once

#include "Constants/Enum.h"
#include "Constants/Marco.h"

#include <cinttypes>
#include <string>
NAMESPACE_BEGIN
class Exchange
{
public:
    // TODO
    static DateType GetContractExpirationDate(DateType date, ExchangeType exchange)
    {
        if (exchange == ExchangeType::BinanceUsdMargin || exchange == ExchangeType::BinanceCoinMargin)
        {
            return GetBinanceExpirationDate(date);
        }
        else
        {
            // ERRORLOG
            return -1;
        }
    }
    
    static DateType GetBinanceExpirationDate(DateType date)
    {
    }

    static DateType GetContractNextExpirationDate(DateType date, ExchangeType exchange)
    {
        if (exchange == ExchangeType::BinanceUsdMargin || exchange == ExchangeType::BinanceCoinMargin)
        {
            return GetBinanceNextExpirationDate(date);
        }
        else
        {
            // ERRORLOG
            return -1;
        }
    }
    
    static DateType GetBinanceNextExpirationDate(DateType date)
    {
    }

};
NAMESPACE_END;