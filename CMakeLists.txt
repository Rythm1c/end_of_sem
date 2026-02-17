cmake_minimum_required(VERSION 3.10)
project(BatteryManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags based on compiler type
if(MSVC)
    # MSVC compiler flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    # GCC/Clang compiler flags (MinGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Source files
set(SOURCES
    main.cc
    admin.cc
    battery.cc
    database.cc
    menus.cc
)

# Create executable
add_executable(project ${SOURCES})

# Set output directory for the executable
set_target_properties(project PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
