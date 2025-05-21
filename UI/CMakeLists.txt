cmake_minimum_required(VERSION 3.16)

project(UI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt6_wrap_ui(UI_HEADERS oknostartowe.ui oknogra1.ui oknogra2.ui)

add_library(UI STATIC
    oknostartowe.cpp oknostartowe.h
    oknogra1.cpp oknogra1.h
    oknogra2.cpp oknogra2.h
    ${UI_HEADERS}
    )

target_link_libraries(UI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets WarstwaBiznesowa)
target_include_directories(UI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

