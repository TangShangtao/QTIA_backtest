cmake_minimum_required(VERSION 3.27)
# 管理三方库
file(GLOB ThirdPartyCmakes cmake/*.cmake)
foreach(ThirdPartyCmake ${ThirdPartyCmakes})
    include(${ThirdPartyCmake})
endforeach()
# message(STATUS "ThirdPartyNames ${ThirdPartyNames}")
# message(STATUS "ThirdPartyIncDir ${ThirdPartyIncDir}")
# message(STATUS "ThirdPartyLnkDir ${ThirdPartyLnkDir}")

project(QTIA_backtest C CXX)

# 编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CXX_FLAGS
    -Wextra
    -Werror
    -march=native
    -std=c++17
    )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")
set(CMAKE_CXX_FLAGES_DEBUG "-O0 -fPIC")
set(CMAKE_CXX_FLAGES_RELEASE "-O3 -DNDEBUG -fPIC")
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif()
# 生成路径 -- 此处相对路径为build/CMakeFiles
set(EXECUTABLE_OUTPUT_PATH ${SolutionRootDir}/bin)
set(LIBRARY_OUTPUT_PATH ${SolutionRootDir}/lib)
set(QTIA_LnkDir ${LIBRARY_OUTPUT_PATH})
set(QTIA_ExeDir ${EXECUTABLE_OUTPUT_PATH})
# 子项目
add_subdirectory(Test)
add_subdirectory(ToolKit)
add_subdirectory(Replayer)
