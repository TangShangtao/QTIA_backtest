/**
 * @file DataDefs.hpp
 * @author Tang Shangtao (2643659274@qq.com)
 * @brief Market Data declaration. 行情数据声明
 * @version 0.1
 * @date 2023-08-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include <string>

struct Level1Depth
{
    double BidPrices[1];
    double BidAmounts[1];
    double AskPrices[1];
    double AskAmounts[1];
};
struct Level5Depth
{
    double BidPrices[5];
    double BidAmounts[5];
    double AskPrices[5];
    double AskAmounts[5];
};
struct Level10Depth
{
    double BidPrices[10];
    double BidAmounts[10];
    double AskPrices[10];
    double AskAmounts[10];
};
struct Level25Depth
{
    double BidPrices[25];
    double BidAmounts[25];
    double AskPrices[25];
    double AskAmounts[25];
};

enum LevelType
{
    One,
    Five,
    Ten,
    TwentyFive
};

// TODO try to use jemalloc or boost mem pool to allocate mem
// TODO add warn log

class DepthState
{
private:
    void*     OrderBookData_;
    LevelType Level_;
    std::string      InstrumentID_;
    std::string      ExchangeID_;
    uint64_t  TimeStamp_;

public:
    DepthState(LevelType level) : TimeStamp_(0)
    {
        switch (level)
        {
        case LevelType::One:
            OrderBookData_ = (void*)new Level1Depth;
            break;
        case LevelType::Five:
            OrderBookData_ = (void*)new Level5Depth;
            break;
        case LevelType::Ten:
            OrderBookData_ = (void*)new Level10Depth;
            break;
        case LevelType::TwentyFive:
            OrderBookData_ = (void*)new Level25Depth;
            break;
        default:
            OrderBookData_ = nullptr;
            break;
        }
        Level_ = level;
    }
    ~DepthState()
    {
        if (OrderBookData_ != nullptr)
        {
            delete OrderBookData_;
        }
    }

public:
    inline LevelType GetLevel()
    {
        return Level_;
    }
    inline void SetInstrumentID(const char* InstrumentID)
    {
        if (InstrumentID == nullptr)
        {
            // WARN LOG
            return;
        }
        InstrumentID_ = InstrumentID;
    }
    inline const char* GetInstrumentID()
    {
        return InstrumentID_.c_str();
    }
    inline void SetExchangeID(const char* ExchangeID)
    {
        if (ExchangeID == nullptr)
        {
            // WARN LOG
            return;
        }
        ExchangeID_ = ExchangeID;
    }
    inline const char* GetExchangeID()
    {
        return ExchangeID_.c_str();
    }
    inline void SetTimeStamp(uint64_t time)
    {
        TimeStamp_ = time;
    }
    inline uint64_t GetTimeStamp()
    {
        return TimeStamp_;
    }
    inline void SetBidPrice(double price, uint8_t level)
    {
        switch (Level_)
        {
        case LevelType::One:
            if (level > 1) return;// WARN LOG
            ((Level1Depth*)OrderBookData_)->BidPrices[level] = price;
            break;
        case LevelType::Five:
            if (level > 5) return;// WARN LOG
            ((Level5Depth*)OrderBookData_)->BidPrices[level] = price;
            break;
        case LevelType::Ten:
            if (level > 10) return;// WARN LOG
            ((Level10Depth*)OrderBookData_)->BidPrices[level] = price;
            break;
        case LevelType::TwentyFive:
            if (level > 25) return;// WARN LOG
            ((Level25Depth*)OrderBookData_)->BidPrices[level] = price;
            break;
        default:
            OrderBookData_ = nullptr;// WARN LOG
            break;
        }
    }
    inline double GetBidPrice(uint8_t level)
    {
        switch (Level_)
        {
        case LevelType::One:
            if (level > 1) return;// WARN LOG
            return ((Level1Depth*)OrderBookData_)->BidPrices[level];
        case LevelType::Five:
            if (level > 5) return;// WARN LOG
            return ((Level5Depth*)OrderBookData_)->BidPrices[level];
        case LevelType::Ten:
            if (level > 10) return;// WARN LOG
            return ((Level10Depth*)OrderBookData_)->BidPrices[level];
        case LevelType::TwentyFive:
            if (level > 25) return;// WARN LOG
            return ((Level25Depth*)OrderBookData_)->BidPrices[level];
        default:
            OrderBookData_ = nullptr;// WARN LOG
            return -1;
        }
    }
    inline void SetBidAmount(double amount, uint8_t level)
    {
        switch (Level_)
        {
        case LevelType::One:
            if (level > 1) return;// WARN LOG
            ((Level1Depth*)OrderBookData_)->BidAmounts[level] = amount;
            break;
        case LevelType::Five:
            if (level > 5) return;// WARN LOG
            ((Level5Depth*)OrderBookData_)->BidAmounts[level] = amount;
            break;
        case LevelType::Ten:
            if (level > 10) return;// WARN LOG
            ((Level10Depth*)OrderBookData_)->BidAmounts[level] = amount;
            break;
        case LevelType::TwentyFive:
            if (level > 25) return;// WARN LOG
            ((Level25Depth*)OrderBookData_)->BidAmounts[level] = amount;
            break;
        default:
            OrderBookData_ = nullptr;// WARN LOG
            break;
        }
    }
    inline double GetBidAmount(uint8_t level)
    {
        switch (Level_)
        {
        case LevelType::One:
            if (level > 1) return;// WARN LOG
            return ((Level1Depth*)OrderBookData_)->BidAmounts[level];
        case LevelType::Five:
            if (level > 5) return;// WARN LOG
            return ((Level5Depth*)OrderBookData_)->BidAmounts[level];
        case LevelType::Ten:
            if (level > 10) return;// WARN LOG
            return ((Level10Depth*)OrderBookData_)->BidAmounts[level];
        case LevelType::TwentyFive:
            if (level > 25) return;// WARN LOG
            return ((Level25Depth*)OrderBookData_)->BidAmounts[level];
        default:
            OrderBookData_ = nullptr;// WARN LOG
            return -1;
        }
    }
    

};