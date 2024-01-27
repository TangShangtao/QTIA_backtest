include(ExternalProject)
include(cmake/config.cmake)

set(magic_enumVer 0.7.3)
set(magic_enumUrl https://github.com/Neargye/magic_enum/archive/refs/tags/v${magic_enumVer}.tar.gz)
set(magic_enumUrlHash SHA256=b8d0cd848546fee136dc1fa4bb021a1e4dc8fe98e44d8c119faa3ef387636bf7)
set(magic_enumRootDir ${ThirdPartyDir}/magic_enum)
set(magic_enumInstall   echo "not install magic_enum")
ExternalProject_Add(magic_enum-${magic_enumVer}
    URL               ${magic_enumUrl}
    URL_HASH          ${magic_enumUrlHash} 
    DOWNLOAD_NAME     magic_enum-${magic_enumVer}.tar.gz
    PREFIX            ${magic_enumRootDir}
    CONFIGURE_COMMAND "" 
    BUILD_COMMAND     "" 
    INSTALL_COMMAND   ${magic_enumInstall} 
    )

set(magic_enumIncludeDir ${magic_enumRootDir}/src/magic_enum-${magic_enumVer}/include)

set(ThirdPartyNames ${ThirdPartyNames} magic_enum-${magic_enumVer})
set(ThirdPartyIncDir ${ThirdPartyIncDir} ${magic_enumIncludeDir})
