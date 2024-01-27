cmake_minimum_required(VERSION 3.27)

project(Backtest C CXX)
set(ProjRootDir ${SolutionRootDir}/Backtest/)

aux_source_directory(${ProjRootDir}/Source src)
add_library(Backtest STATIC ${src})

#依赖--头文件、库文件
add_dependencies(Backtest ${ThirdPartyNames})
# message(${ThirdPartyIncDir})
target_include_directories(Backtest
    PUBLIC "${SolutionRootDir}/Public/Include"
    PUBLIC "${SolutionRootDir}/ToolKit/Include"
    PUBLIC "${SolutionRootDir}/Backtest/Include"
    PUBLIC "${ThirdPartyIncDir}"
    PUBLIC "${SolutionRootDir}"
)
target_link_directories(Backtest
    PUBLIC "${ThirdPartyLnkDir}"
    PUBLIC "${QTIA_LnkDir}"
)
target_link_libraries(Backtest
    PUBLIC ToolKit
    PUBLIC Replayer
    PUBLIC Matcher
    PUBLIC Strategy
    PUBLIC OrdMgr
)