#include "TradePublisher.h"

namespace QB
{
namespace Matcher
{

class SimpleMatcher : TradePublisher
{
private:
    
private:
    virtual void MatchOrder(OBSSPtr marketData) override;
    void MatchLogic(OBSSPtr marketData);
};

};
};