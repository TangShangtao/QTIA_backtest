cmake_minimum_required(VERSION 3.5)

project(Test C CXX)

add_executable(${PROJECT_NAME} main.cpp)

#依赖--头文件、库文件
add_dependencies(${PROJECT_NAME} ${ThirdPartyNames})
message(STATUS "ThirdPartyNames ${ThirdPartyNames}")
target_include_directories(${PROJECT_NAME}
    PUBLIC "${PROJECT_SOURCE_DIR}/Public/Include"
    PUBLIC "${fmtIncludeDir}"
    PUBLIC "${spdlogIncludeDir}"
    PUBLIC "${yaml-cppIncludeDir}"
)
target_link_directories(${PROJECT_NAME}
    PUBLIC "${SolutionRootDir}/lib"
    PUBLIC "${fmtLibDir}"
    PUBLIC "${spdlogLibDir}"
    PUBLIC "${yaml-cppLibDir}"
)
target_link_libraries(${PROJECT_NAME}
    PUBLIC libfmt.a
    PUBLIC libyaml-cpp.a
    PUBLIC dl
    PUBLIC pthread
)