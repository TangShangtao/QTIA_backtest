#pragma once

#include "Constant/Using.h"

#include <memory>
#include <string>

namespace QB
{

class Pnl
{
public:
    double      unReal_{0};
    double      real_{0};

    double      fee_{0};
    TimeStamp   updateTime_{0};
    std::string quoteCurrForCalc_;
};

using PnlSPtr = std::shared_ptr<Pnl>;
using PnlUPtr = std::unique_ptr<Pnl>;

};