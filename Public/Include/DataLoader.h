// created by tangshangtao 0916
#pragma once

#include "Constant/Enum.h"
#include "Constant/Marco.h"
#include "Data/Orderbook.h"
#include "Data/IncrementalOrderbook.h"

class DataLoader
{
    virtual bool LoadRawData2Cache(std::string& symbol, DateType date) {};

};