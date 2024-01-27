cmake_minimum_required(VERSION 3.27)

project(OrdMgr C CXX)
set(ProjRootDir ${SolutionRootDir}/OrdMgr)

aux_source_directory(${ProjRootDir}/Source src)
add_library(OrdMgr STATIC ${src})

#依赖--头文件、库文件
add_dependencies(OrdMgr ${ThirdPartyNames})
# message(${ProjRootDir}/Include)
target_include_directories(OrdMgr
    PUBLIC "${SolutionRootDir}/Public/Include"
    PUBLIC "${SolutionRootDir}/ToolKit/Include"
    PUBLIC "${ThirdPartyIncDir}"
    PUBLIC "${ProjRootDir}/Include"
    PUBLIC "${SolutionRootDir}"

)
target_link_directories(OrdMgr
    PUBLIC "${ThirdPartyLnkDir}"
    PUBLIC "${QTIA_LnkDir}"
)
target_link_libraries(OrdMgr
    PUBLIC ToolKit
)