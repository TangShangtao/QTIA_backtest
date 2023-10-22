include(ExternalProject)
include(cmake/config.cmake)

set(arrowVer 13.0.0)
set(arrowUrl https://github.com/apache/arrow/archive/refs/tags/apache-arrow-${arrowVer}.tar.gz)
set(arrowUrlHash SHA256=99c27e6a517c750f29c3e6b264836e31251bb8e978dbbf11316680ca3eb8ebda)
set(arrowRootDir ${ThirdPartyDir}/arrow)
set(arrowConfigure cd ../arrow-${arrowVer}/cpp && mkdir build && cd build && cmake ..)
set(arrowBuild     cd ../arrow-${arrowVer}/cpp && cd build && make CXXFLAGS+='-fPIC')
set(arrowInstall   echo "not install arrow")
ExternalProject_Add(arrow-${arrowVer}
    URL               ${arrowUrl}
    URL_HASH          ${arrowUrlHash} 
    DOWNLOAD_NAME     arrow-${arrowVer}.tar.gz
    PREFIX            ${arrowRootDir}
    CONFIGURE_COMMAND ${arrowConfigure} 
    BUILD_COMMAND     ${arrowBuild} 
    INSTALL_COMMAND   ${arrowInstall} 
    )

set(arrowIncludeDir ${arrowRootDir}/src/arrow-${arrowVer}/cpp/src)
set(arrowLibDir ${arrowRootDir}/src/arrow-${arrowVer}/cpp/build/release)
configure_file(${arrowRootDir}/src/arrow-${arrowVer}/cpp/src/parquet/parquet_version.h.in ${arrowRootDir}/src/arrow-${arrowVer}/cpp/src/parquet/parquet_version.h @ONLY)

set(ThirdPartyNames ${ThirdPartyNames} arrow-${arrowVer})
set(ThirdPartyIncDir ${ThirdPartyIncDir} ${arrowIncludeDir})
set(ThirdPartyIncDir ${ThirdPartyIncDir} ${arrowRootDir}/src/arrow-${arrowVer}/cpp/build/src)
set(ThirdPartyLnkDir ${ThirdPartyLnkDir} ${arrowLibDir})

