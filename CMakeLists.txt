cmake_minimum_required(VERSION 3.13.4)

# Project's name
project(3D-rotations)

FIND_PACKAGE(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)# network audio)

# Show a message with the opencv version detected 
MESSAGE("SFML version : ${SFML_VERSION}") 

find_package (Threads)

###################################
###################################
###################################

# Location where cmake first looks for cmake modules.
#set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

##---------------------------------------------------
## Please set your wxWidgets configuration here
##--------------------------------------------------- 
 
# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.
#find_package(wxWidgets COMPONENTS core base REQUIRED)
 
##---------------------------------------------------
## Actual config file starts here
##--------------------------------------------------- 
 
# wxWidgets include (this will do all the magic to configure everything)
#include( "${wxWidgets_USE_FILE}" )


###################################
###################################
###################################


set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(release 0)

if(release)
	add_definitions(-DNDEBUG)
endif()

set(SOURCES
	animation.cpp
	base.cpp
	camera.cpp
	noise.cpp
	platonic.cpp
	shape.cpp
)

#MESSAGE("SFML +lib : ${SFML_LIBRARIES}") 

add_executable(animation-app ${SOURCES})

# link required libs
#target_link_libraries(animation-app ${SFML_LIBRARIES})

target_link_libraries(animation-app sfml-system sfml-window sfml-graphics )
target_link_libraries(animation-app ${CMAKE_THREAD_LIBS_INIT} )

# install resources
#add_subdirectory(resources)
