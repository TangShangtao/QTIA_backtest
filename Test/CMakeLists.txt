cmake_minimum_required(VERSION 3.27)

project(Test C CXX)
set(ProjRootDir ${SolutionRootDir}/Test/)

add_executable(Test ${ProjRootDir}/main.cpp)

#依赖--头文件、库文件
add_dependencies(Test ${ThirdPartyNames})
# message(${ThirdPartyIncDir})
target_include_directories(Test
    PUBLIC "${SolutionRootDir}/Public/Include"
    PUBLIC "${SolutionRootDir}/ToolKit/Include"
    PUBLIC "${ThirdPartyIncDir}"
)
target_link_directories(Test
    PUBLIC "${ThirdPartyLnkDir}"
    PUBLIC "${QTIA_LnkDir}"
)
target_link_libraries(Test
    PUBLIC ToolKit
)