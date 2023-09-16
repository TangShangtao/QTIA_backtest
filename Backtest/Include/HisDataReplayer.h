// created by tangshangtao 0916
#pragma once

#include "Constant/Enum.h"
#include "Constant/Marco.h"
#include "Data/Orderbook.h"
#include "Data/IncrementalOrderbook.h"
#include "BaseClass/Observer.h"
#include "BaseClass/DataLoader.h"

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <yaml.h>
NAMESPACE_BEGIN

class HisDataReplayer
{
private:
    typedef std::vector<IncrementalOrderbook> RawDataList;
    std::unordered_map<std::string, RawDataList> raw_data_cache_;

    std::unordered_set<ExchangeObserver*> observers_;

    DataLoader* loader_;

public:
    bool Init(YAML::Node cfg);
    void Run();
    void RunParallel();   

    inline void RegisterObserver(ExchangeObserver* observer)
    {
        observers_.insert(observer);
    }
    
    
};

NAMESPACE_END;