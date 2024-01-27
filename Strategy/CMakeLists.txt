cmake_minimum_required(VERSION 3.27)

project(Strategy C CXX)
set(ProjRootDir ${SolutionRootDir}/Strategy)

aux_source_directory(${ProjRootDir}/Source src)
add_library(Strategy STATIC ${src})

#依赖--头文件、库文件
add_dependencies(Strategy ${ThirdPartyNames})
# message("${ProjRootDir}/Include")
target_include_directories(Strategy
    PUBLIC "${SolutionRootDir}/Public/Include"
    PUBLIC "${SolutionRootDir}/ToolKit/Include"
    PUBLIC "${ThirdPartyIncDir}"
    PUBLIC "${ProjRootDir}/Include"
    PUBLIC "${SolutionRootDir}"

)
target_link_directories(Strategy
    PUBLIC "${ThirdPartyLnkDir}"
    PUBLIC "${QTIA_LnkDir}"
)
target_link_libraries(Strategy
    PUBLIC ToolKit
)