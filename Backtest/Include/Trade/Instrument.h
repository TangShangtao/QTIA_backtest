//
// Created by TangShangtao on 2023/8/28.
//

#pragma once

#include "Constants/Marco.h"
#include "Constants/Enum.h"
#include "../Utils.h"
#include "Trade/Exchange.h"

#include <string>
#include <vector>
#include <cinttypes>
#include <array>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

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

    DateType            expiration_date_;
    DurationType        change_contract_dt_;

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
    static json apiconfig_;
    static DateType main_contract_change_duration_;

public:
    Instrument(
        const char* instrument_id, 
        ExchangeType exchange_id, 
        InstrumentType contract_type, 
        CurrencyType base_ccy, 
        CurrencyType quote_ccy, 
        bool trading = true
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
        auto parse_name = StrUtils::SplitString(instrument_id_, '_');
        std::string exchange_id = parse_name[0];
        std::string symbol = parse_name[1];
        instrument_type_class_ = GetInstrumentTypeClass();
        // TODO 逻辑?
        if (instrument_type_class_ != InstrumentTypeClass::Spot)
        {
            std::vector<std::string> keys = 
            {"Exchanges", exchange_id, "Future_size_precision", symbol};
            std::string tmp = NestedGet(apiconfig_, keys);
            future_size_precision_ = std::stoi(tmp.c_str());
            if (instrument_type_class_ == InstrumentTypeClass::ReverseFuture)
            {
                settlement_ccy_ = base_ccy_;
                keys = {"Exchanges", exchange_id, "Future_contract_usd_face", symbol};
                tmp = NestedGet(apiconfig_, keys);
                if (tmp == "")
                {
                    // ERROR LOG
                    return;
                }
                future_contract_usd_ = std::stoi(tmp.c_str());
            }
            else if (instrument_type_class_ == InstrumentTypeClass::ForwardFuture)
            {
                settlement_ccy_ = quote_ccy_;
            }

        }
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

    void GetContractExpirationDate(DurationType dt, ExchangeType exchange)
    {
        DateType expiration_date = Exchange::GetContractNextExpirationDate(dt, exchange_id_);
        DateType next_expiration_date = Exchange::GetContractNextExpirationDate(dt, exchange_id_);
        
        if (contract_type_ == InstrumentType::FutureThisQuarter)
        {
            if (dt <= (expiration_date - main_contract_change_duration_))
            {
                expiration_date_ = expiration_date;
            }
            else
            {
                expiration_date_ = next_expiration_date;
            }
        }
        else if (contract_type_ == InstrumentType::FutureNextQuarter)
        {
            if (dt <= (expiration_date - main_contract_change_duration_))
            {
                expiration_date_ = next_expiration_date;
            }
            else
            {
                expiration_date_ = expiration_date;
            }
        }
        change_contract_dt_ = expiration_date - main_contract_change_duration_;

    }

    static std::string NestedGet(const json& root, const std::vector<std::string>& keys) 
    {
        json obj = root;
        for (const auto& key : keys) 
        {
            if (!obj.contains(key)) 
            {
                return ""; 
            }
            obj = obj[key];
        }
        return obj;
    }
};
std::ifstream f("../../common/apiconfig.json");
json Instrument::apiconfig_ = json::parse(f);

NAMESPACE_END;





