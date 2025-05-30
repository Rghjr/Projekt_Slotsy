cmake_minimum_required(VERSION 3.16)

project(Gra2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(UI_HEADERS)
qt6_wrap_ui(UI_HEADERS oknogra2.ui)

add_library(Gra2 STATIC
        oknogra2.cpp
        oknogra2.h
	${UI_HEADERS}
)

target_link_libraries(Gra2 PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(Gra2 PUBLIC ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
