include(ExternalProject)
include(cmake/config.cmake)

set(spdlogVer 1.12.0)
set(spdlogUrlHash SHA256=4dccf2d10f410c1e2feaff89966bfc49a1abb29ef6f08246335b110e001e09a9)

set(spdlogRootDir ${ThirdPartyDir}/spdlog)
set(spdlogIncludeDir ${spdlogRootDir}/src/spdlog-${spdlogVer}/include)
set(spdlogLibDir ${spdlogRootDir}/src/spdlog-${spdlogVer}/build)

set(spdlogUrl https://github.com/gabime/spdlog/archive/refs/tags/v${spdlogVer}.tar.gz)
set(spdlogConfigure cd ../spdlog-${spdlogVer} && mkdir build && cd build && cmake ..)
set(spdlogBuild     cd ../spdlog-${spdlogVer} && cd build && make CXXFLAGS+='-fPIC')
set(spdlogInstall   echo "install spdlog")

ExternalProject_Add(spdlog-${spdlogVer}
    URL               ${spdlogUrl}
    URL_HASH          ${spdlogUrlHash} 
    DOWNLOAD_NAME     spdlog-${spdlogVer}.tar.gz
    PREFIX            ${spdlogRootDir}
    CONFIGURE_COMMAND ${spdlogConfigure} 
    BUILD_COMMAND     ${spdlogBuild} 
    INSTALL_COMMAND   ${spdlogInstall} 
    )

set(ThirdPartyNames ${ThirdPartyNames} spdlog-${spdlogVer})
# if (NOT EXISTS ${spdlogRootDir}/src/spdlog-${spdlogVer})
#     add_custom_target(rescan-spdlog ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS spdlog-${spdlogVer})
# else()
#     add_custom_target(rescan-spdlog)
# endif()