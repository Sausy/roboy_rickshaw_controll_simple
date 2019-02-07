cmake_minimum_required(VERSION 2.8.3)
project(rickshaw_ctl)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

SET(CMAKE_BUILD_TYPE Debug)

#==============================================================================
# Dependencies
#==============================================================================
find_package(catkin REQUIRED COMPONENTS
        roscpp
        std_msgs
        message_generation
        tf
        tf_conversions
        visualization_msgs
        roboy_middleware_msgs
        roboy_control_msgs
        common_utilities
        )

catkin_package(CATKIN_DEPENDS
        message_runtime
        roboy_middleware_msgs
        roboy_control_msgs
        common_utilities
        )

include_directories(
        include/
        ${catkin_INCLUDE_DIRS}
)
#==============================================================================
# Application
#==============================================================================
FILE(GLOB SRC_FILES src/*.cpp)
FILE(GLOB INCLUDE_FILES include/*.hpp)

add_executable( roboy_rickshaw_controll_simple
        ${SRC_FILES}
        ${INCLUDE_FILES}
        )
add_dependencies(roboy_rickshaw_controll_simple roboy_middleware_msgs_gencpp roboy_control_msgs_gencpp)
target_link_libraries( roboy_rickshaw_controll_simple -lpthread -lrt ${catkin_LIBRARIES})
