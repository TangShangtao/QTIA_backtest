//
// Created by TangShangtao on 2023/8/28.
//

#pragma once

#include "constants/marco.h"
#include "constants/enum.h"

#include <string>
#include <chrono>
#include <cinttypes>
#include <array>
#include <algorithm>

NAMESPACE_BEGIN
class Instrument
{
private:
    std::string         instrument_id_;
    ExchangeType        exchange_id_;
    InstrumentType      contract_type_;
    CurrencyType        base_ccy_;
    CurrencyType        quote_ccy_;
    bool                trading_;
    // tm or uint?
    std::uint64_t       expiration_date_;
    std::uint64_t       expiration_dt_;
    std::uint64_t       change_contract_dt;

    InstrumentTypeClass instrument_type_class_;
    double              future_size_precision_;
    CurrencyType        settlement_ccy_;
    std::int8_t         future_contract_usd_;
    double              future_multiple_;

    constexpr static std::array<ExchangeType, 6> FORWARD_FUTURES_EXCHANGES
    {
        ExchangeType::HuobiPerpUSDT,
        ExchangeType::HuobiPerpUSDTCross,
        ExchangeType::Bitasset,
        ExchangeType::BinanceUsdMargin,
        ExchangeType::NewOkcoinUSDT,
        ExchangeType::Ftx
    };

public:
    Instrument(
        const char* instrument_id, 
        ExchangeType exchange_id, 
        InstrumentType contract_type, 
        CurrencyType base_ccy, 
        CurrencyType quote_ccy, 
        bool trading
        ):   
        instrument_id_(instrument_id),
        exchange_id_(exchange_id),
        contract_type_(contract_type),
        base_ccy_(base_ccy),
        quote_ccy_(quote_ccy),
        trading_(trading)
    {
        Process();
    }
    ~Instrument()
    {
        
    }
private:
    void Process()
    {
        instrument_type_class_ = GetInstrumentTypeClass();
        // TODO
    }
    InstrumentTypeClass GetInstrumentTypeClass() const
    {
        if (contract_type_ == InstrumentType::Spot)
        {
            return InstrumentTypeClass::Spot;
        }
        bool in_ffexchanges = std::find(FORWARD_FUTURES_EXCHANGES.begin(), FORWARD_FUTURES_EXCHANGES.end(), exchange_id_) != FORWARD_FUTURES_EXCHANGES.end();
        if (contract_type_ == InstrumentType::FutureLTFX || in_ffexchanges)
        {
            return InstrumentTypeClass::ForwardFuture;
        }
        if (exchange_id_ == ExchangeType::BitMEX && quote_ccy_ == CurrencyType::BTC)
        {
            return InstrumentTypeClass::ForwardFuture;
        }
        if (exchange_id_ == ExchangeType::BitMEX && quote_ccy_ != CurrencyType::BTC && base_ccy_ != CurrencyType::BTC)
        {
            return InstrumentTypeClass::Quanto;
        }
        if (exchange_id_ == ExchangeType::Ig || exchange_id_ == ExchangeType::Yahoo)
        {
            return InstrumentTypeClass::CFD;
        }
        return InstrumentTypeClass::ReverseFuture;

    }


};
NAMESPACE_END;




