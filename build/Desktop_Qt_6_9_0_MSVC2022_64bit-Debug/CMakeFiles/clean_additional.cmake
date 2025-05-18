# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Slots_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Slots_autogen.dir\\ParseCache.txt"
  "Slots_autogen"
  "UI\\CMakeFiles\\UI_autogen.dir\\AutogenUsed.txt"
  "UI\\CMakeFiles\\UI_autogen.dir\\ParseCache.txt"
  "UI\\UI_autogen"
  "WarstwaBiznesowa\\CMakeFiles\\WarstwaBiznesowa_autogen.dir\\AutogenUsed.txt"
  "WarstwaBiznesowa\\CMakeFiles\\WarstwaBiznesowa_autogen.dir\\ParseCache.txt"
  "WarstwaBiznesowa\\WarstwaBiznesowa_autogen"
  )
endif()
