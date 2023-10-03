cmake_minimum_required(VERSION 3.5)
# 管理三方库
file(GLOB ThirdPartyList cmake/*.cmake)
foreach(ThirdPartyLib ${ThirdPartyList})
    include(${ThirdPartyLib})
endforeach()
# 编译选项
project(QTIA_backtest C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CXX_FLAGS
    -Wextra
    -Werror
    -march=native
    )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")
set(CMAKE_CXX_FLAGES_DEBUG "-O0 -fPIC")
set(CMAKE_CXX_FLAGES_RELEASE "-O3 -DNDEBUG -fPIC")
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif()
# 生成路径 -- 此处相对路径为build/CMakeFiles
set(EXECUTABLE_OUTPUT_PATH ../../bin)
set(LIBRARY_OUTPUT_PATH ../../lib)
# 项目属性
add_subdirectory(Test)

