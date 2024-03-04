# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Laborator_10_11_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Laborator_10_11_autogen.dir\\ParseCache.txt"
  "Laborator_10_11_autogen"
  )
endif()
