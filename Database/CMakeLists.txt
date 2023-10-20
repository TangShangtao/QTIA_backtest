cmake_minimum_required(VERSION 3.27)

project(Database C CXX)
set(ProjRootDir ${SolutionRootDir}/Database/)
aux_source_directory(${ProjRootDir}/Source src)
add_library(Database STATIC ${src})

#依赖--头文件、库文件
add_dependencies(Database ${ThirdPartyNames})
target_include_directories(Database
    PUBLIC "${SolutionRootDir}/Public/Include"
    PUBLIC "${SolutionRootDir}/ToolKit/Include"
    PUBLIC "${ThirdPartyIncDir}"
    PUBLIC "${ProjRootDir}/Include"
)
target_link_directories(Replayer
    PUBLIC "${ThirdPartyLnkDir}"
    PUBLIC "${QTIA_LnkDir}"
)
target_link_libraries(Replayer
    PUBLIC ToolKit
)