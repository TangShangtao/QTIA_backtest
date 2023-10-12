#include "Logger.h"

using namespace QB;
int main()
{
    ToolKit::Logger::Init("./config/logger.yaml");
    INFO("hello world");
}