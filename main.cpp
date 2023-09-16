#include <iostream>

#include "trade_types/instrument_type.h"

using namespace backtest;

int main() 
{
    Instrument test = Instrument("BinanceCoinMargin_BTCUSD_quarter", ExchangeType::BinanceUsdMargin, InstrumentType::FutureNextQuarter, CurrencyType::BTC, CurrencyType::USD);
}
