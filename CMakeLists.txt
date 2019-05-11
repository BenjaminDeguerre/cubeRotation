cmake_minimum_required(VERSION 3.1.0)

project(cubeRotation)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core REQUIRED)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${PROJECT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})

# Populate a CMake variable with the sources
set(SRCS
    src/linerotationdialog.cpp
    src/main.cpp
    src/mainview.cpp
    src/mainwindow.cpp
    src/viewpositiondialog.cpp
)

qt5_wrap_cpp(SRC
    include/linerotationdialog.hpp
    include/mainview.hpp
    include/mainwindow.hpp
    include/viewpositiondialog.hpp
    include/scene.hpp
    include/scenebasic.hpp
    )

qt5_wrap_ui(UIS_HDRS
    forms/linerotationdialog.ui
    forms/mainwindow.ui
    forms/viewpositiondialog.ui
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Tell CMake to create the helloworld executable
add_executable(cubeRotation ${SRCS} ${UIS_HDRS} ${SRC})

# Use the Widgets module from Qt 5
target_link_libraries(cubeRotation Qt5::Widgets)