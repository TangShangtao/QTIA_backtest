cmake_minimum_required(VERSION 3.27)

project(Matcher C CXX)
set(ProjRootDir ${SolutionRootDir}/Matcher)

aux_source_directory(${ProjRootDir}/Source src)
add_library(Matcher STATIC ${src})

#依赖--头文件、库文件
add_dependencies(Matcher ${ThirdPartyNames})
# message(${ProjRootDir}/Include)
target_include_directories(Matcher
    PUBLIC "${SolutionRootDir}/Public/Include"
    PUBLIC "${SolutionRootDir}/ToolKit/Include"
    PUBLIC "${ThirdPartyIncDir}"
    PUBLIC "${ProjRootDir}/Include"
    PUBLIC "${SolutionRootDir}"

)
target_link_directories(Matcher
    PUBLIC "${ThirdPartyLnkDir}"
    PUBLIC "${QTIA_LnkDir}"
)
target_link_libraries(Matcher
    PUBLIC ToolKit
)