#pragma once

#include "Constant/Enum.h"

#include <memory>

namespace QB
{

class Position
{
    ExchangeType     exchange_;
    SymbolType       symbolType_;
    std::string      symbol_;

    PosDirectionType posDirection_;

    double           fee_{0};
    double           pos_{0};
    double           prePos_{0};
    double           avgOpenPrice_{0};
    double           preAvgOpenPrice_{0};
    double           pnlUnReal_{0};
    double           pnlReal_{0};
    double           totalBidVol_{0};
    double           totalAskVol_{0};
    double           preTotalBidVol_{0};
    double           preTotalAskVol_{0};
    double           totalOpenVol_{0};
    double           preTotalOpenVol_{0};
    std::uint64_t    lastNoUsedToCalcPos_{0};
    std::uint64_t    updateTime_;
};
using PositionSPtr = std::shared_ptr<Position>;
using PositionUPtr = std::unique_ptr<Position>;

};