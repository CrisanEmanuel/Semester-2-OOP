# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Simulare_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Simulare_autogen.dir\\ParseCache.txt"
  "Simulare_autogen"
  )
endif()
