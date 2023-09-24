cmake_minimum_required(VERSION 3.14)

project(lightsheet_microscopy_image_optimization LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(lightsheet_microscopy_image_optimization
    run2steps.h
    openCLHelper.h
    exceptions.h
    main.cpp
    helper.h
)


########################
## OpenCL integration ##
########################
find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
LINK_DIRECTORIES(${OpenCL_LIBRARY})

target_link_libraries(lightsheet_microscopy_image_optimization Qt${QT_VERSION_MAJOR}::Core ${OpenCL_LIBRARIES})

install(TARGETS lightsheet_microscopy_image_optimization
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
