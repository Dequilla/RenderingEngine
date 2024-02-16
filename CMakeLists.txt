cmake_minimum_required(VERSION 3.21)

#####################
set(EXEC_NAME "RenderingEngine")
set(INC_DIR "include/" "vendor/")
set(SRC_DIR "src/")
set(SOURCE_FILES 
    "main.cpp"

    "graphics/model.cpp"
    "graphics/shader.cpp"
    "graphics/renderer.cpp"

    "graphics/model_formats/wavefront_obj.cpp"

    "system/window.cpp"
    "system/clock.cpp"

    "platform/x11/x11_window.cpp"

    "platform/opengl/opengl.cpp"
    "platform/opengl/gl_model.cpp"
    "platform/opengl/gl_shader.cpp"
    "platform/opengl/gl_renderer3d.cpp"
)

# Transforms
list(TRANSFORM SOURCE_FILES PREPEND ${SRC_DIR})

# Compiler 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2a")
set(CMAKE_CXX_STANDARD 20) 
set(TARGET_COMPILE_FEATURES cxx_std_20)
set(CMAKE_C_COMPILER "gcc-13")
set(CMAKE_CXX_COMPILER "g++-13")

option(RENDERER_OPENGL "Compile with OpenGL as rendering implementation." OFF)
option(WINDOW_MGR_X11 "Compile with x11 as window manager." ON)

project(
    ${EXEC_NAME}
    VERSION 0.1
    DESCRIPTION "Rendering Engine."
    LANGUAGES CXX
)

#####################

if(WIN32)
    add_compile_definitions(WIN32)
elseif(UNIX)
    add_compile_definitions(UNIX)
endif()

if(WINDOW_MGR_X11)
    add_compile_definitions(__x11__)
else()
    message(FATAL_ERROR "No window manager selected. Set one of \"WINDOW_MGR_X11\" to ON/TRUE")
endif()

if(RENDERER_OPENGL)
    add_compile_definitions(__opengl__)
else()
    message(FATAL_ERROR "No renderer selected when compiling. Set one of \"RENDERER_OPENGL\" to ON/TRUE")
endif()

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -g -O3")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O0")

####k##################################
# Libraries 
######################################

find_package(X11)
if(NOT X11_FOUND)
    message(SEND_ERROR "Not found: X11")
endif()

find_package(OpenGL)
if(NOT OPENGL_FOUND)
    message(SEND_ERROR "Not found: OpenGL")
endif()

set(
    LIBRARIES_TO_LINK
    ${OPENGL_LIBRARIES}
    ${X11_X11_LIB}
)

add_executable(${EXEC_NAME} ${SOURCE_FILES})

target_include_directories(${EXEC_NAME} PUBLIC ${INC_DIR})
target_compile_features(${EXEC_NAME} PUBLIC ${TARGET_COMPILE_FEATURES})
target_link_libraries(${EXEC_NAME} ${LIBRARIES_TO_LINK})

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_compile_definitions(${EXEC_NAME} PRIVATE _DEBUG)
else()
    target_compile_definitions(${EXEC_NAME} PRIVATE _RELEASE)
endif()
