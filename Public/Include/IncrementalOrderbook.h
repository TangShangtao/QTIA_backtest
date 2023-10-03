// created by tangshangtao 0916
#pragma once

#include "Constant/Enum.h"
#include "Constant/Marco.h"

#include <string>
// TODO not implenmented, just some fields
class IncrementalOrderbook
{
public:
    ExchangeType    exchange_;
    std::string     symbol_;
    DateType        date_;
    TimeType        time_;
    SideType        side_;
    float           price_;
    std::uint64_t   amount_;



};