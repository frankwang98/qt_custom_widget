cmake_minimum_required(VERSION 3.16)
project(QtCustomWidgets VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(WIDGET_SOURCES
    battery.cpp dashboard.cpp compasswidget.cpp ringprogresswidget.cpp
    switchbutton.cpp ledindicator.cpp speedometer.cpp)
set(WIDGET_HEADERS
    battery.h dashboard.h compasswidget.h ringprogresswidget.h
    switchbutton.h ledindicator.h speedometer.h)

add_library(qt_custom_widgets STATIC ${WIDGET_SOURCES} ${WIDGET_HEADERS})
target_link_libraries(qt_custom_widgets PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(qt_custom_widgets PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_compile_features(qt_custom_widgets PUBLIC cxx_std_17)

option(BUILD_WIDGET_DEMO "Build the interactive widget gallery" ON)
if(BUILD_WIDGET_DEMO)
    add_executable(qt_widget_gallery main.cpp mainwindow.cpp mainwindow.h
        mainwindow.ui style.qrc)
    target_link_libraries(qt_widget_gallery PRIVATE qt_custom_widgets)
endif()
