include(ExternalProject)
include(cmake/config.cmake)

set(fmtVer 10.1.1)
set(fmtUrl https://github.com/fmtlib/fmt/archive/refs/tags/${fmtVer}.tar.gz)
set(fmtUrlHash SHA256=78b8c0a72b1c35e4443a7e308df52498252d1cefc2b08c9a97bc9ee6cfe61f8b)
set(fmtRootDir ${ThirdPartyDir}/fmt)
set(fmtConfigure cd ../fmt-${fmtVer} && mkdir build && cd build && cmake ..)
set(fmtBuild     cd ../fmt-${fmtVer} && cd build && make CXXFLAGS+='-fPIC')
set(fmtInstall   echo "not install fmt")
ExternalProject_Add(fmt-${fmtVer}
    URL               ${fmtUrl}
    URL_HASH          ${fmtUrlHash} 
    DOWNLOAD_NAME     fmt-${fmtVer}.tar.gz
    PREFIX            ${fmtRootDir}
    CONFIGURE_COMMAND ${fmtConfigure} 
    BUILD_COMMAND     ${fmtBuild} 
    INSTALL_COMMAND   ${fmtInstall} 
    )

set(fmtIncludeDir ${fmtRootDir}/src/fmt-${fmtVer}/include)
set(fmtLibDir ${fmtRootDir}/src/fmt-${fmtVer}/build)

set(ThirdPartyNames ${ThirdPartyNames} fmt-${fmtVer})
set(ThirdPartyIncDir ${fmtIncludeDir})
set(ThirdPartyLnkDir ${fmtLibDir})

# if (NOT EXISTS ${fmtRootDir}/src/fmt-${fmtVer})
#     add_custom_target(rescan-fmt ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS fmt-${fmtVer})
# else()
#     add_custom_target(rescan-fmt)
# endif()