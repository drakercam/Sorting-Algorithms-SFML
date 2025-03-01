cmake_minimum_required(VERSION 3.10)
project(vs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML
find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics window system audio)
include_directories(${CMAKE_SOURCE_DIR}/src ${SFML_INCLUDE_DIR})

# Add all source files
set(SOURCES
    main.cpp
    sorting.cpp
    handler.cpp
)

set(HEADERS
    sorting.h
    handler.h
)

# Create executable
add_executable(vs ${SOURCES} ${HEADERS})

# CMakeLists.txt
add_custom_command(TARGET vs POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/textures
    $<TARGET_FILE_DIR:vs>/textures
)

# Link SFML libraries
target_link_libraries(vs PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
