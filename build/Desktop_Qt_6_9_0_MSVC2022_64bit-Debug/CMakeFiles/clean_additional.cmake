# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Slots_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Slots_autogen.dir\\ParseCache.txt"
  "Slots_autogen"
  )
endif()
