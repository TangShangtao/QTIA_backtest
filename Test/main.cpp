#include "Logger.h"

using namespace QB;
int main()
{
    ToolKit::InitLogger("./config/logger.yaml");
    INFO("hello world");
}