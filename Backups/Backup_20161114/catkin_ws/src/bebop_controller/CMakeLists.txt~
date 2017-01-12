cmake_minimum_required(VERSION 2.8.3)
project(bebop_controller)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare ROS messages and services
add_message_files(FILES Num.msg)
add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)
#generate_messages(DEPENDENCIES geometry_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(keyboard_controller src/keyboard_controller.cpp)
target_link_libraries(keyboard_controller ${catkin_LIBRARIES})
add_dependencies(keyboard_controller bebop_controller_generate_messages_cpp)

add_executable(BebopController src/BebopController.cpp)
target_link_libraries(BebopController ${catkin_LIBRARIES})
add_dependencies(BebopController bebop_controller_generate_messages_cpp)

add_executable(DirectionController src/DirectionController.cpp)
target_link_libraries(DirectionController ${catkin_LIBRARIES})
add_dependencies(DirectionController bebop_controller_generate_messages_cpp)

add_executable(SpeedController src/SpeedController.cpp)
target_link_libraries(SpeedController ${catkin_LIBRARIES})
add_dependencies(SpeedController bebop_controller_generate_messages_cpp)


add_executable(Agent src/Agent.cpp)
target_link_libraries(Agent ${catkin_LIBRARIES})
add_dependencies(Agent bebop_controller_generate_messages_cpp)



