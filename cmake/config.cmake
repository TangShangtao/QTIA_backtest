get_filename_component(SolutionRootDir "${CMAKE_CURRENT_LIST_DIR}" DIRECTORY)
set(SolutionRootDir ${SolutionRootDir} "" CACHE STRING "root dir of solution QTIA_backtest")
set(ThirdPartyDir ${SolutionRootDir}/ThirdParty)
