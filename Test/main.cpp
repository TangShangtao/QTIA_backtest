#include "CsvLoader.h"
#include <iostream>

using namespace QB::ToolKit;


int main()
{
    std::string path = "/home/tangshangtao/test_data/20230101/EXCHANGE_BINANCE.BTC-USDT.SECURITY_TYPE_PERP.CONTRACT_TYPE_LINEAR.USDT.UNSPECIFIED_bookSnapshot5_20230101.csv";
    // std::string path = "../../data_for_shangtao/20230901/log.txt";
    auto loader = CsvLoader();
    loader.LoadFile(path);    
    loader.CoutColumn();
    // loader.NextRow();
    // loader.CoutCurrentRow();
    auto data = loader.ToOrderbookSnapshort();
    std::cout << data->bids[2].Volume << std::endl;
}