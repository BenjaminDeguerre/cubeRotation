cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(cubeRotation)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH bin)

find_package(Qt5 REQUIRED COMPONENTS Core Gui OpenGL)


file(GLOB_RECURSE source_file "src/*" "include/*")

include_directories(include)

add_executable(cubeRotation ${source_file})
qt5_use_modules(cubeRotation Widgets OpenGL)
target_link_libraries(cubeRotation -lGL -lGLEW -lGLU ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
