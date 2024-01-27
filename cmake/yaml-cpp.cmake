include(ExternalProject)
include(cmake/config.cmake)

set(yaml-cppVer 0.8.0)
set(yaml-cppUrl https://github.com/jbeder/yaml-cpp/archive/refs/tags/${yaml-cppVer}.tar.gz)
set(yaml-cppUrlHash SHA256=fbe74bbdcee21d656715688706da3c8becfd946d92cd44705cc6098bb23b3a16)
set(yaml-cppRootDir ${ThirdPartyDir}/yaml-cpp)
set(yaml-cppConfigure cd ../yaml-cpp-${yaml-cppVer} && mkdir build && cd build && cmake ..)
set(yaml-cppBuild     cd ../yaml-cpp-${yaml-cppVer} && cd build && make CXXFLAGS+='-fPIC')
set(yaml-cppInstall   echo "not install yaml-cpp")
ExternalProject_Add(yaml-cpp-${yaml-cppVer}
    URL               ${yaml-cppUrl}
    URL_HASH          ${yaml-cppUrlHash} 
    DOWNLOAD_NAME     yaml-cpp-${yaml-cppVer}.tar.gz
    PREFIX            ${yaml-cppRootDir}
    CONFIGURE_COMMAND ${yaml-cppConfigure} 
    BUILD_COMMAND     ${yaml-cppBuild} 
    INSTALL_COMMAND   ${yaml-cppInstall} 
    )

set(yaml-cppIncludeDir ${yaml-cppRootDir}/src/yaml-cpp-${yaml-cppVer}/include)
set(yaml-cppLibDir ${yaml-cppRootDir}/src/yaml-cpp-${yaml-cppVer}/build)

set(ThirdPartyNames ${ThirdPartyNames} yaml-cpp-${yaml-cppVer})
set(ThirdPartyIncDir ${ThirdPartyIncDir} ${yaml-cppIncludeDir})
set(ThirdPartyLnkDir ${ThirdPartyLnkDir} ${yaml-cppLibDir})
# if (NOT EXISTS ${yaml-cppRootDir}/src/yaml-cpp-${yaml-cppVer})
#     add_custom_target(rescan-yaml-cpp ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS yaml-cpp-${yaml-cppVer})
# else()
#     add_custom_target(rescan-yaml-cpp)
# endif()