#pragma once
#include <vector>

#include "Protocol.h"
#include "BaseClass/Subscriber.h"

namespace QB
{

class PnlCalculator : public TradeSubscriber
{
public:
    void Init(int capital, double riskfree);
    void OnRtnTrade(TradeSPtr trade) override;
    void ShowOutPut();
private:    
    int capital;
    double riskfree;

    double totalFee;
    double totalEarn;
    std::vector<double> returnPerTrade; // 每笔成交的收益率
    std::vector<int> signalPerTrade;    // 每笔成交


};


};
