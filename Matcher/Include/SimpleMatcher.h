#include "TradePublisher.h"

namespace QB
{
namespace Matcher
{

class SimpleMatcher : TradePublisher
{
private:
    virtual void MatchOrder(OBSSPtr marketData) override;

};

};
};