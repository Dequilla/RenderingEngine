cmake_minimum_required(VERSION 3.21)

#####################
set(EXEC_NAME "RenderingEngine")
set(INC_DIR "include/")
set(SRC_DIR "src/")
set(SOURCE_FILES 
    "main.cpp"
    "window.cpp"
    "shader.cpp"
    "platform/opengl.cpp"
)

# Transforms
list(TRANSFORM SOURCE_FILES PREPEND ${SRC_DIR})
list(TRANSFORM INCLUDE_FILES PREPEND ${INC_DIR})

# Compiler 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2a")
set(CMAKE_CXX_STANDARD 20) 
set(TARGET_COMPILE_FEATURES cxx_std_20)
set(CMAKE_C_COMPILER "gcc-13")
set(CMAKE_CXX_COMPILER "g++-13")

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

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -g -O3")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O0")

######################################
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
