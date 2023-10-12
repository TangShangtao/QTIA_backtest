#pragma once

#include "Constant/Enum.h"

#include <string>
#include <memory>

namespace QB
{


class Symbol
{
public:
    ExchangeType exchange_;
    std::string  symbol_;
    SymbolType   symbolType_;

};
using SymbolSPtr = std::shared_ptr<Symbol>;
using SymbolUPtr = std::unique_ptr<Symbol>;
};