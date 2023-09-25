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
# 生成路径
set(EXECUTABLE_OUTPUT_PATH ${SolutionRootDir}/bin)
set(LIBRARY_OUTPUT_PATH ${SolutionRootDir}/lib)
# 项目属性
# aux_source_directory(Backtest/Replayer SrcList)
# set(SrcList ${SrcList} main.cpp)
add_executable(${PROJECT_NAME} main.cpp)
# target_link_options(Crypto_backtest_cpp PUBLIC "LINKER:--copy-dt-needed-entries")
# if(${CMAKE_BUILD_TYPE} MATCHES Debug)
#     message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
#     set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "-d")
#     set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJ_VER} SOVERSION ${MAJOR_VER})
# else()
#     message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
#     set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJ_VER} SOVERSION ${MAJOR_VER})
# endif()
#依赖--头文件、库文件
add_dependencies(${PROJECT_NAME} ${ThirdPartyNames})
message(STATUS "ThirdPartyNames ${ThirdPartyNames}")
target_include_directories(${PROJECT_NAME}
    PUBLIC "${PROJECT_SOURCE_DIR}/Backtest/Include"
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



set(EXECUTABLE_OUTPUT_PATH ../bin)
set(LIBRARY_OUTPUT_PATH)
