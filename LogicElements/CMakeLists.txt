cmake_minimum_required(VERSION 3.5)

project(logic_elements LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(FLTK_SKIP_FLUID True)
set(OpenGL_GL_PREFERENCE "GLVND")

find_package(FLTK REQUIRED)
find_package(OpenGL REQUIRED)


set(GRAPHLIB_DIR ".")

include_directories(
    ${GRAPHLIB_DIR}
    SYSTEM
    ${FLTK_INCLUDE_DIR}
)

link_directories(
    ${FLTK_INCLUDE_DIR}/../lib
)

add_executable(
    logic_elements
    ${GRAPHLIB_DIR}/Graph_lib/Graph.cpp
    ${GRAPHLIB_DIR}/Graph_lib/Graph.h
    ${GRAPHLIB_DIR}/Graph_lib/GUI.cpp
    ${GRAPHLIB_DIR}/Graph_lib/GUI.h
    ${GRAPHLIB_DIR}/Graph_lib/Window.cpp
    ${GRAPHLIB_DIR}/Graph_lib/Window.h
    ${GRAPHLIB_DIR}/Graph_ext.cpp
    ${GRAPHLIB_DIR}/Graph_ext.h
    logic.cpp
    logic.h
    logic_shapes.cpp
    logic_shapes.h
    main.cpp
)

target_link_libraries(
    logic_elements
    ${FLTK_LIBRARIES}
    fltk_png
    fltk_z
    fltk_jpeg
    ${OPENGL_LIBRARIES}
)

install(TARGETS logic_elements)
