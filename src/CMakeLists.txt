cmake_minimum_required(VERSION 2.8)

# This project is designed to be built outside the Shark source tree.
# set Shark_DIR to the proper location
project(ExampleProject)

# Find the Shark libraries and includes
find_package(Shark REQUIRED)
include(${SHARK_USE_FILE})

# Executable
#add_executable(ExampleProject HelloWorld.cpp)
#target_link_libraries(ExampleProject ${SHARK_LIBRARIES})

# Library
add_library(sharkwrapper SHARED sharkwrapper.cpp)
set_property(TARGET sharkwrapper PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(sharkwrapper ${SHARK_LIBRARIES})
#add_compile_options(-fPIC)
# copy shared object to sharkwrapper directory
#add_custom_command(TARGERT sharkwrapper POST_BUILD COMMAND $(CMAKE_COMMAND) -E copy $<TARGET_FILE:sharkwrapper> ../sharkwrapper)
