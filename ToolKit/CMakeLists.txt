cmake_minimum_required(VERSION 3.27)

project(ToolKit C CXX)
set(ProjRootDir ${SolutionRootDir}/ToolKit/)
aux_source_directory(${ProjRootDir}/Source src)
add_library(ToolKit STATIC ${src})
#依赖--头文件、库文件
add_dependencies(ToolKit ${ThirdPartyNames})
target_include_directories(ToolKit
    PUBLIC "${SolutionRootDir}/Public/Include"
    PUBLIC "${SolutionRootDir}/ToolKit/Include"
    PUBLIC "${ThirdPartyIncDir}"
)
target_link_directories(ToolKit
    PUBLIC "${ThirdPartyLnkDir}"
    PUBLIC "${QTIA_LnkDir}"
)
target_link_libraries(ToolKit
    PUBLIC libfmt.a
    PUBLIC libyaml-cpp.a
    PUBLIC libspdlog.a
    # PUBLIC libarrow.a
    # PUBLIC libarrow_bundled_dependencies.a
    PUBLIC dl
    PUBLIC libjemalloc.a
    PUBLIC pthread
)