include(ExternalProject)
include(cmake/config.cmake)
# 需要安装autoconf
set(jemallocVer 5.3.0)
set(jemallocUrl https://github.com/jemalloc/jemalloc/archive/refs/tags/${jemallocVer}.tar.gz)
set(jemallocUrlHash SHA256=ef6f74fd45e95ee4ef7f9e19ebe5b075ca6b7fbe0140612b2a161abafb7ee179)
set(jemallocRootDir ${ThirdPartyDir}/jemalloc)
set(jemallocConfigure cd ../jemalloc-${jemallocVer} && ./autogen.sh)
set(jemallocBuild     cd ../jemalloc-${jemallocVer} && make CXXFLAGS+='-fPIC')
set(jemallocInstall   echo "not install jemalloc")
ExternalProject_Add(jemalloc-${jemallocVer}
    URL               ${jemallocUrl}
    URL_HASH          ${jemallocUrlHash} 
    DOWNLOAD_NAME     jemalloc-${jemallocVer}.tar.gz
    PREFIX            ${jemallocRootDir}
    CONFIGURE_COMMAND ${jemallocConfigure} 
    BUILD_COMMAND     ${jemallocBuild} 
    INSTALL_COMMAND   ${jemallocInstall} 
    )

set(jemallocIncludeDir ${jemallocRootDir}/src/jemalloc-${jemallocVer}/include)
set(jemallocLibDir ${jemallocRootDir}/src/jemalloc-${jemallocVer}/lib)

set(ThirdPartyNames ${ThirdPartyNames} jemalloc-${jemallocVer})
set(ThirdPartyIncDir ${ThirdPartyIncDir} ${jemallocIncludeDir})
set(ThirdPartyLnkDir ${ThirdPartyLnkDir} ${jemallocLibDir})