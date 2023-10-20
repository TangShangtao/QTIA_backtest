include(ExternalProject)
include(cmake/config.cmake)

set(clickhouse-cppVer 2.5.1)
set(clickhouse-cppUrl https://github.com/ClickHouse/clickhouse-cpp/archive/refs/tags/v${clickhouse-cppVer}.tar.gz)
set(clickhouse-cppUrlHash SHA256=8942fc702eca1f656e59c680c7e464205bffea038b62c1a0ad1f794ee01e7266)
set(clickhouse-cppRootDir ${ThirdPartyDir}/clickhouse-cpp)
set(clickhouse-cppConfigure cd ../clickhouse-cpp-${clickhouse-cppVer} && mkdir build && cd build && cmake ..)
set(clickhouse-cppBuild     cd ../clickhouse-cpp-${clickhouse-cppVer} && cd build && make CXXFLAGS+='-fPIC')
set(clickhouse-cppInstall   echo "not install clickhouse-cpp")
ExternalProject_Add(clickhouse-cpp-${clickhouse-cppVer}
    URL               ${clickhouse-cppUrl}
    URL_HASH          ${clickhouse-cppUrlHash} 
    DOWNLOAD_NAME     clickhouse-cpp-${clickhouse-cppVer}.tar.gz
    PREFIX            ${clickhouse-cppRootDir}
    CONFIGURE_COMMAND ${clickhouse-cppConfigure} 
    BUILD_COMMAND     ${clickhouse-cppBuild} 
    INSTALL_COMMAND   ${clickhouse-cppInstall} 
    )

set(clickhouse-cppIncludeDir ${clickhouse-cppRootDir}/src/clickhouse-cpp-${clickhouse-cppVer})
# set(clickhouse-cppLibDir ${clickhouse-cppRootDir}/src/clickhouse-cpp-${clickhouse-cppVer}/build)

set(ThirdPartyNames ${ThirdPartyNames} clickhouse-cpp-${clickhouse-cppVer})
set(ThirdPartyIncDir ${ThirdPartyIncDir} ${clickhouse-cppIncludeDir})
set(ThirdPartyIncDir ${ThirdPartyIncDir} ${clickhouse-cppIncludeDir}/contrib/absl)
# set(ThirdPartyLnkDir ${ThirdPartyLnkDir} ${clickhouse-cppLibDir})
