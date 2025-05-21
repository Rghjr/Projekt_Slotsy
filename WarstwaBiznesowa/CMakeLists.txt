cmake_minimum_required(VERSION 3.16)

project(WarstwaBiznesowa LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(WarstwaBiznesowa SHARED
  WarstwaBiznesowa_global.h
  gra1mechaniki.cpp gra1mechaniki.h
  gra2mechaniki.h gra2mechaniki.cpp
)

target_link_libraries(WarstwaBiznesowa PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(WarstwaBiznesowa PRIVATE WARSTWABIZNESOWA_LIBRARY)

target_include_directories(WarstwaBiznesowa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
