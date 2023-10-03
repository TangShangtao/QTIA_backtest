include(ExternalProject)
include(cmake/config.cmake)

set(fmtVer 10.1.1)
set(fmtUrlHash SHA256=78b8c0a72b1c35e4443a7e308df52498252d1cefc2b08c9a97bc9ee6cfe61f8b)

set(fmtRootDir ${ThirdPartyDir}/fmt)
set(fmtIncludeDir ${fmtRootDir}/src/fmt-${fmtVer}/include)
set(fmtLibDir ${fmtRootDir}/src/fmt-${fmtVer}/build)

set(fmtUrl https://github.com/fmtlib/fmt/archive/refs/tags/${fmtVer}.tar.gz)
set(fmtConfigure cd ../fmt-${fmtVer} && mkdir build && cd build && cmake ..)
set(fmtBuild     cd ../fmt-${fmtVer} && cd build && make CXXFLAGS+='-fPIC')
set(fmtInstall   echo "install fmt")

ExternalProject_Add(fmt-${fmtVer}
    URL               ${fmtUrl}
    URL_HASH          ${fmtUrlHash} 
    DOWNLOAD_NAME     fmt-${fmtVer}.tar.gz
    PREFIX            ${fmtRootDir}
    CONFIGURE_COMMAND ${fmtConfigure} 
    BUILD_COMMAND     ${fmtBuild} 
    INSTALL_COMMAND   ${fmtInstall} 
    )

set(ThirdPartyNames ${ThirdPartyNames} fmt-${fmtVer})
# if (NOT EXISTS ${fmtRootDir}/src/fmt-${fmtVer})
#     add_custom_target(rescan-fmt ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS fmt-${fmtVer})
# else()
#     add_custom_target(rescan-fmt)
# endif()